#include "Voiture_gestionnaire.hpp"

Voiture_gestionnaire::Voiture_gestionnaire()
{
    for (int i = 0; i < 4; i++) {
        for(int j = 0; j < nb_voitures_max; j++) {
            tabVoitures[i][j] = NULL;
        }
    }
    posVoitureTete = 10000;
    niveau = 1;
}

Voiture_gestionnaire::~Voiture_gestionnaire()
{
    for (int i = 0; i < 4; i++) {
        for(int j = 0; j < nb_voitures_max; j++) {
            delete tabVoitures[i][j];
            tabVoitures[i][j] = NULL;
        }
    }
}

void Voiture_gestionnaire::afficherVoitures(SDL_Texture* carsTexture)
{
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < nb_voitures_max; j++) {
            if (tabVoitures[i][j] != NULL) {
                tabVoitures[i][j]->afficher(carsTexture);
            }
        }
    }
}

void Voiture_gestionnaire::chargement(Route* route, int distance_parcourue)
{
    if(niveau < 3) {
        chargement_voitures_fichier(route, distance_parcourue);
    } else {
        //chargement_aleatoire(route, distance_parcourue);
    }
}

/* Créé de nouvelles voitures et les positionne par rapport aux fichiers de niveaux */
void Voiture_gestionnaire::chargement_voitures_fichier(Route* route, int distance_parcourue)
{
    static int nbChargements = 0;
    if (distance_parcourue > 2000 * nbChargements && posVoitureTete > -500)
    {
        if(!fichier.is_open()) {
            if(niveau == 1) {
                fichier.open("autres/niveau1");
            } else {
                fichier.open("autres/niveau2");
            }
        }
        string line;
        if(!getline(fichier, line)) {
            fichier.close();
            niveau++;
        } else {
            for( int i = 0 ; i < 4 ; i++) {
                if(line[i] == '1' || line[i] == '2') {
                    int j = 0;
                    while (tabVoitures[i][j] != NULL) {
                        j++; //On trouve une place libre dans le tableau de pointeurs de voitures
                    }
                    if (j < nb_voitures_max) {
                        int position_x = route->getPosX() + i * route->getLargeurVoiePlateau();
                        tabVoitures[i][j] = new Voiture(position_x, -1000, route->getLargeurVoiePlateau()-10, rand()%8);
                        if(line[i] == '1') {
                            tabVoitures[i][j]->setVitesseVoiture(10);
                        }
                        else if (line[i] == '2') {
                            tabVoitures[i][j]->setVitesseVoiture(15);
                        }
                    }
                }
            }
        }
        nbChargements++;
    }
}

void Voiture_gestionnaire::chargement_aleatoire(Route* route, int distance_parcourue)
{
    
}

void Voiture_gestionnaire::MegaFonction(int vitesse, SDL_Rect* rectVoitureJoueur)
{
    posVoitureTete = 10000;
    bool flagCollision = false;
    bool changeDeVoie = false;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < nb_voitures_max; j++) {
            if (tabVoitures[i][j] != NULL) {
                if(not isDead(i,j)) {
                    tabVoitures[i][j]->avancer(vitesse);
                    checkVoitTete(i, j);
                    changeDeVoie = depassementNEW(i, j);
//                    if(collisionVoitJoueur(i, j, rectVoitureJoueur)) {
//                        flagCollision = true;
//                    }
                    if(changeDeVoie) {
                        changementVoieGauche(i, j); //On place la voiture dans le tableau de gauche
                    }
                }
            }
        }
    }
}

/* Détruit la voiture si elle est trop bas */
bool Voiture_gestionnaire::isDead(int i, int j)
{
    if (tabVoitures[i][j]->getPosY() > LEVEL_HEIGHT + 2000) {
        delete tabVoitures[i][j];
        tabVoitures[i][j] = NULL;
        return true;
    }
    return false;
}

/* Actualise la position de la voiture en tête */
void Voiture_gestionnaire::checkVoitTete(int i, int j)
{
    int posTemp = tabVoitures[i][j]->getPosY();
    if(posTemp < posVoitureTete) {
        posVoitureTete = posTemp;
    }
}

/* Gère le dépassement des voitures */
bool Voiture_gestionnaire::depassementNEW(int i, int j)
{
    for(int k = 0; k < nb_voitures_max; k++) {
        if(tabVoitures[i][k] != NULL && tabVoitures[i][j]->getVitesseVoiture() > tabVoitures[i][k]->getVitesseVoiture()) {
            int posYVoit1 = tabVoitures[i][j]->getPosY();
            int posYVoit2 = tabVoitures[i][k]->getPosY() + tabVoitures[i][k]->getHeight();
            if(posYVoit1 > posYVoit2 && abs(posYVoit1 - posYVoit2) < 500) {
                if(i == 0) {
                    tabVoitures[i][j]->freiner(1);
                }else{
                    tabVoitures[i][j]->deplacer(-4,0); //Dépassement à gauche
                    int coteDroVoit1 = tabVoitures[i][j]->getPosX() + tabVoitures[i][j]->getWidth();
                    int coteGauVoit2 = tabVoitures[i][k]->getPosX();
                    if(coteDroVoit1 < (coteGauVoit2 + 5)) {
                        return true;
                    }
                }
            }
        }
    }
    return false;
}

/* Place une voitre tab[i] dans tab[i-1] */
void Voiture_gestionnaire::changementVoieGauche(int i, int j)
{
    int k = 0;
    while (tabVoitures[i-1][k] != NULL) { // Cherhce une place dans le tableau
        k++;
    }
    tabVoitures[i-1][k] = tabVoitures[i][j];
    tabVoitures[i][j] = NULL;
}

/* Vérifie si il y a une collision entre la voiture et la voiture Joueur */
SDL_bool Voiture_gestionnaire::collisionVoitJoueur(int i, int j, SDL_Rect* rectVoitureJoueur)
{
    SDL_bool collision;
    SDL_Rect intersect;
    return collision = SDL_IntersectRect(rectVoitureJoueur, tabVoitures[i][j]->getRectCollision(), &intersect);
}
