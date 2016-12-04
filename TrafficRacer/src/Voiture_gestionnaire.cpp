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

void Voiture_gestionnaire::chargement(Route* route)
{
    if(niveau < 3) {
        chargement_voitures_fichier(route);
    } else {
        chargement_aleatoire(route);
    }
}

/* Créé de nouvelles voitures et les positionne par rapport aux fichiers de niveaux */
void Voiture_gestionnaire::chargement_voitures_fichier(Route* route)
{
    static int nbChargements = 0;
    if (posVoitureTete > -300)
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

void Voiture_gestionnaire::chargement_aleatoire(Route* route)
{
    if(posVoitureTete > -500) {
        int voie = rand()%4;
        int i = 0;
        while (tabVoitures[voie][i] != NULL) {
            i++; //On trouve une place libre dans le tableau de pointeurs de voitures
        }
        if(i < nb_voitures_max) {
            int position_x = route->getPosX() + voie * route->getLargeurVoiePlateau();
            tabVoitures[voie][i] = new Voiture(position_x, -1000, route->getLargeurVoiePlateau()-10, rand()%8);
            tabVoitures[voie][i]->setVitesseVoiture(rand()%9 + 10);
        }
    }
}

/* Gère les voitures et renvois true si collision */
bool Voiture_gestionnaire::gestion(int vitesse, SDL_Rect* rectVoitureJoueur)
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
                    changeDeVoie = depassement(i, j);
                    if(collisionVoitJoueur(i, j, rectVoitureJoueur)) {
                        flagCollision = true;
                    }
                    if(changeDeVoie) {
                        changementVoieGauche(i, j); //On place la voiture dans le tableau de gauche
                    }
                }
            }
        }
    }
    return flagCollision;
}

/* Détruit la voiture si elle est trop bas */
bool Voiture_gestionnaire::isDead(int i, int j)
{    if (tabVoitures[i][j]->getPosY() > LEVEL_HEIGHT + 2000) {
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
bool Voiture_gestionnaire::depassement(int i, int j)
{
    for(int k = 0; k < nb_voitures_max; k++) {
        if(tabVoitures[i][k] != NULL && tabVoitures[i][j]->getVitesseVoiture() > tabVoitures[i][k]->getVitesseVoiture()) {
            int posYVoit1 = tabVoitures[i][j]->getPosY();
            int posYVoit2 = tabVoitures[i][k]->getPosY() + tabVoitures[i][k]->getHeight();
            if(posYVoit1 > posYVoit2 && abs(posYVoit1 - posYVoit2) < 500) {
                if(i == 0) {
                    tabVoitures[i][j]->freiner(1);
                } else {
                    if(tabVoitures[i][j]->getChangementVoie() || peutDepasser(i, j) ) {
                        tabVoitures[i][j]->setChangementVoie(true);
                        tabVoitures[i][j]->deplacer(-4,0); //Dépassement à gauche
                        int coteDroVoit1 = tabVoitures[i][j]->getPosX() + tabVoitures[i][j]->getWidth();
                        int coteGauVoit2 = tabVoitures[i][k]->getPosX();
                        if(coteDroVoit1 < (coteGauVoit2 + 5)) {
                            return true;
                        }
                    } else {
                        tabVoitures[i][j]->freiner(1);
                    }
                }
            }
        }
    }
    return false;
}

bool Voiture_gestionnaire::peutDepasser(int i, int j) {
    int posYvoit = tabVoitures[i][j]->getPosY();
    int heightVoit = tabVoitures[i][j]->getHeight();
    int posYhaut = posYvoit - 2 * heightVoit; //On recherche si il y a assez de place dans la voie de gauche
    int posYbas = posYvoit + heightVoit;
    for(int k = 0; k < nb_voitures_max; k++) {
        if (tabVoitures[i-1][k] != NULL) {
            int posYvoitTemp = tabVoitures[i-1][k]->getPosY();
            if(posYvoitTemp > posYhaut && posYvoitTemp < posYbas) {
                return false;
            }
        }
    }
    return true;
}

/* Place une voitre tab[i] dans tab[i-1] */
void Voiture_gestionnaire::changementVoieGauche(int i, int j)
{
    tabVoitures[i][j]->setChangementVoie(false);
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
    collision = SDL_IntersectRect(rectVoitureJoueur, tabVoitures[i][j]->getRectCollision(), &intersect);
    if (collision && tabVoitures[i][j]->getPosY() > rectVoitureJoueur->y ) {
        tabVoitures[i][j]->setVitesseVoiture(2);
    }
    return collision;
}

/* Accélère la voiture devant la voiture joueur */
void Voiture_gestionnaire::klaxon(Route* route, SDL_Rect* rectVoitureJoueur) {
    int posXtemp = route->getPosX() + route->getLargeurVoiePlateau();
    int posXvoit = rectVoitureJoueur->x + (rectVoitureJoueur->w/2);
    int voie = 0;
    while(posXvoit > posXtemp) {
        posXtemp += route->getLargeurVoiePlateau();
        voie++;
    }
    int positionMin = -10000;
    int j = -1;
    for(int i = 0; i < nb_voitures_max; i++) { // On cherche la voiture juste devant
        if(tabVoitures[voie][i] != NULL) {
            int posYtemp = tabVoitures[voie][i]->getPosY();
            if(posYtemp > positionMin && posYtemp < rectVoitureJoueur->y) {
                positionMin = tabVoitures[voie][i]->getPosY();
                j = i;
            }
        }
    }
    if(j>=0 && tabVoitures[voie][j]->getVitesseVoiture() < 19) {
        tabVoitures[voie][j]->accelerer(2);
    }
}
