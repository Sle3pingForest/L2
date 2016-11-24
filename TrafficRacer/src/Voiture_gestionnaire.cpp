#include "Voiture_gestionnaire.hpp"
std::ifstream infile;
ifstream fichier("autres/niveau2", ios::in);

Voiture_gestionnaire::Voiture_gestionnaire()
{
    for (int i = 0; i < 4; i++)
    {
        for(int j = 0; j < nb_voitures_max; j++)
        {
            tabVoitures[i][j] = NULL;
            nb_voitures_Voie[i] = 0;
        }
    }
    posVoitureTete = 10000;

}

// Gère les déplacements, les suppressions de voitures et renvoie true si collision
bool Voiture_gestionnaire::gestion_voitures(int vitesse, SDL_Rect* rectVoitureJoueur)
{
    SDL_bool collision;
    SDL_Rect intersect;
    bool flagCollision = false;
    posVoitureTete = 10000;
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < nb_voitures_max; j++)
        {
            if (tabVoitures[i][j] != NULL)
            {
                if (tabVoitures[i][j]->isDead())
                {
                    delete tabVoitures[i][j];
                    tabVoitures[i][j] = NULL;
                    nb_voitures_Voie[i]--;
                }
                else
                {
                    tabVoitures[i][j]->avancer(vitesse);
                    int posTemp = tabVoitures[i][j]->getPosY();
                    if(tabVoitures[i][j]->getPosY() < posVoitureTete)
                    {
                        posVoitureTete = posTemp;
                    }
                    collision = SDL_IntersectRect(rectVoitureJoueur, tabVoitures[i][j]->getRectCollision(), &intersect);
                    if (collision)
                    {
                        flagCollision = true;
                        if (intersect.x > rectVoitureJoueur->x)
                        {
                            //printf("Droite");
                        }
                        else
                        {
                            //printf("Gauche");
                        }
                        if (intersect.y == rectVoitureJoueur->y)
                        {
                            tabVoitures[i][j]->vitesse ++;
                        }
                    }
                }
            }
        }
    }
    //printf("%d\n", posVoitureTete);
    return flagCollision;
}

// Créer de nouvelles voitures et les positionner par rapport aux fichiers de niveaux
void Voiture_gestionnaire::chargement_voitures_fichier(Route* route, int distance_parcourue)
{
    static int nbChargements = 0;
    if (distance_parcourue > 4000*nbChargements && posVoitureTete > -500)
    {
        string line;
        fichier >> line;
        for( int i = 0 ; i < 4 ; i++)
        {
            if(line[i] == '1' || line[i] == '2')
            {
                //On trouve une place libre dans le tableau de pointeurs de voitures
                int j = 0;
                while (tabVoitures[i][j] != NULL)
                {
                    j++;
                }

                if (j < nb_voitures_max)
                {
                    int position_x = route->getPosX() + i * route->getLargeurVoiePlateau();
                    tabVoitures[i][j] = new Voiture(position_x, -1000, route->getLargeurVoiePlateau()-10, rand()%8);
                    nb_voitures_Voie[i]++;
                    if(line[i] == '1')
                    {
                        tabVoitures[i][j]->setVitesseVoiture(10);
                    }
                    else if (line[i] == '2')
                    {
                        tabVoitures[i][j]->setVitesseVoiture(15);
                    }
                }
            }
        }
        infile.close();
        timerChargementFichier.start();
        nbChargements++;
    }
}

void Voiture_gestionnaire::afficherVoitures(SDL_Texture* carsTexture)
{
    for(int i = 0 ; i < 4; i++)
    {
        for(int j = 0 ; j < nb_voitures_max; j++)
        {
            if (tabVoitures[i][j] != NULL)
            {
                tabVoitures[i][j]->afficher(carsTexture);
                if(i == 2)
                {
                    printf("voit : %d %d\n",j ,tabVoitures[i][j]->getPosY());
                }
            }
        }
    }
}

void Voiture_gestionnaire::depassement(Route *route)
{
    for( int i = 0; i < 4; i++)
    {
        if(nb_voitures_Voie[i] > 1)
        {
            for( int j = 0; j < nb_voitures_max; j++)
            {
                if(tabVoitures[i][j] != NULL)
                {
                    for( int k = 0; k < nb_voitures_max; k++)
                    {
                        if(tabVoitures[i][k] != NULL
                                && tabVoitures[i][j]->getVitesseVoiture() > tabVoitures[i][k]->getVitesseVoiture()
                                && tabVoitures[i][j]->getPosY() - abs( tabVoitures[i][k]->getPosY()) < 300 )
                            // Voiture non NULL si la première est plus rapide que la seconde
                        {
                            bool collision = false;
                            int coteGauV1 = tabVoitures[i][j]->getPosX();
                            int coteDroV1 = coteGauV1 + tabVoitures[i][j]->getWidth();
                            int coteGauV2 = tabVoitures[i][k]->getPosX();
                            int coteDroV2 = coteGauV2 + tabVoitures[i][k]->getWidth();
                            int coteHautV1 = tabVoitures[i][j]->getPosY();
                            int coteBasV1 = coteHautV1 + tabVoitures[i][j]->getHeight();
                            int coteHautV2 = tabVoitures[i][k]->getPosY();
                            int coteBasV2 = coteHautV2 + tabVoitures[i][k]->getHeight();
                            // Si la deuxième voiture est devant la première il y a collision
                            if(coteGauV1 >= coteGauV2 && coteGauV1 <= coteDroV2)
                            {
                                collision = true;
                            }
                            else if(coteDroV1 >= coteGauV2 && coteDroV1 <= coteDroV2)
                            {
                                collision = true;
                            }
                            else if(coteGauV1 <= coteDroV2 && coteHautV1 >= coteBasV2 && coteHautV1 <= coteHautV2)
                            {
                                collision = true;
                            }
                            else if(coteGauV1 <= coteDroV2 && coteBasV1 >= coteBasV2 && coteBasV1 <= coteHautV2)
                            {
                                collision = true;
                            }
                            // La voiture double par la gauche ou ralentit si on est dans la première voie
                            if(collision )
                            {
                                if(tabVoitures[i][j]->getPosX() < route->getPosX() + route->getLargeurVoiePlateau())
                                {
                                    if(tabVoitures[i][j]->getVitesseVoiture() > tabVoitures[i][k]->getVitesseVoiture())
                                    {
                                        tabVoitures[i][j]->setVitesseVoiture(tabVoitures[i][j]->getVitesseVoiture() - 1);//ralenti voie 0
                                    }
                                }
                                else  //Dépassement à gauche
                                {
                                    tabVoitures[i][j]->deplacer(-2,0);
                                    coteGauV1 = tabVoitures[i][j]->getPosX();
                                    coteDroV1 = coteGauV1 + tabVoitures[i][j]->getWidth();
                                    coteGauV2 = tabVoitures[i][k]->getPosX();
                                    if(coteDroV1 < coteGauV2)
                                    {
                                        changementVoieGauche(i, j);//On place la voiture dans le tableau de gauche
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}
/*Attention si pas de place dans tableau*/
void Voiture_gestionnaire::changementVoieGauche(int i, int j)
{
    int k = 0;
    while (tabVoitures[i-1][k] != NULL)
    {
        k++;
    }
    tabVoitures[i-1][k] = tabVoitures[i][j];
    tabVoitures[i][j] = NULL;
}
