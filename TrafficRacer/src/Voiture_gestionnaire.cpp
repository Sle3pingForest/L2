#include "Voiture_gestionnaire.hpp"
std::ifstream infile;
ifstream fichier("autres/niveau2", ios::in);

Voiture_gestionnaire::Voiture_gestionnaire()
{
    for (int i = 0; i < nb_voitures_max; ++i)
    {
        tabVoitures[i] = NULL;
    }
    nb_voitures = 0;
    timerChargementFichier.start();
}

// Gère les déplacements, les suppressions de voitures et renvoie true si collision
bool Voiture_gestionnaire::gestion_voitures(int vitesse, SDL_Rect* rectVoitureJoueur)
{
    SDL_bool collision;
    SDL_Rect intersect;
    bool flagCollision = false;
    for (int i = 0; i < nb_voitures_max; ++i)
    {
        if (tabVoitures[i] != NULL)
        {
            if (tabVoitures[i]->isDead())
            {
                delete tabVoitures[i];
                tabVoitures[i] = NULL;
                 nb_voitures--;
            }
            else
            {
                tabVoitures[i]->avancer(vitesse);
                collision = SDL_IntersectRect(rectVoitureJoueur, tabVoitures[i]->getRectCollision(), &intersect);
                if (collision)
                {
                    flagCollision = true;
                    SDL_Rect positionFenetre;
                    //Calcul du déplacement
                    positionFenetre.x = (intersect.x * echelle) - camera.x;
                    positionFenetre.y = (intersect.y * echelle) - camera.y;
                    //Calcul du redimensionnement
                    positionFenetre.w = intersect.w * echelle;
                    positionFenetre.h = intersect.h * echelle;
                    SDL_SetRenderDrawColor(pRenderer, 255, 0, 0, 200);
                    SDL_RenderFillRect(pRenderer, &positionFenetre);
//                    printf("Colission Voiture %d\n", i);
//                    SDL_Rect* test = tabVoitures[i]->getRectCollision();
//                    printf("Voit x:%d y:%d w:%d h:%d\n", test->x, test->y, test->w, test->h);
//                    printf("inter x:%d y:%d w:%d h:%d\n", intersect.x, intersect.y, intersect.w, intersect.h);
//                    printf("inter x:%d y:%d w:%d h:%d\n", positionFenetre.x, positionFenetre.y, positionFenetre.w, positionFenetre.h);
                    if (intersect.x > rectVoitureJoueur->x) {
                        printf("Droite");
                    }else{
                        printf("Gauche");
                    }
                    if (intersect.y == rectVoitureJoueur->y) {
                        tabVoitures[i]->vitesse ++;
                    }
                }
            }
        }
    }
    return flagCollision;
}


/// ATTENTION NE PAS METTRE PLUS DE 20 VOITURES DANS LE FICHIER ///
// Créer de nouvelles voitures et les positionner par rapport aux fichiers de niveaux
void Voiture_gestionnaire::chargement_voitures_fichier(Route* route)
{
    //infile.open("autres/niveau2");
    if (timerChargementFichier.getTicks() > 3000)
    {
        string line;
        //getline(infile, line);
        fichier >> line;
        for( int i = 0 ; i < 4 ; ++i)
        {
            if(line[i] == '1' || line[i] == '2')
            {
                //On trouve une place libre dans le tableau de pointeurs de voitures
                int j = 0;
                while (tabVoitures[j] != NULL)
                {
                    ++j;
                }

                if (j < nb_voitures_max)
                {
                    int position_x = route->getPosX() + i * route->getLargeurVoiePlateau();
                    tabVoitures[j] = new Voiture(position_x, -600, route->getLargeurVoiePlateau()-10, rand()%8);
                    tabVoitures[j]->setVoie(i+1);
                    ++nb_voitures;
                    if(line[i] == '1')
                    {
                        tabVoitures[j]->setVitesseVoiture(10);
                    }
                    else if (line[i] == '2')
                    {
                        tabVoitures[j]->setVitesseVoiture(17);
                    }
                }

            }
        }
        infile.close();
        timerChargementFichier.start();
    }
}

void Voiture_gestionnaire::afficherVoitures(SDL_Texture* carsTexture)
{
    for(int i = 0 ; i < nb_voitures_max; i++)
    {
        if (tabVoitures[i] != NULL)
        {
            tabVoitures[i]->afficher(carsTexture);
            //SDL_SetRenderDrawColor(pRenderer, 0, 0, 255, 150);
            //tabVoitures[i]->afficherRectCollision();
        }
    }
}

void Voiture_gestionnaire::depassement(Route *route)
{
    if(nb_voitures > 1)
    {
        for( int i = 0; i < nb_voitures_max; i++)
        {
            if( tabVoitures[i] != NULL) // Voiture non NULL
            {
                for(int j = 0; j < nb_voitures_max; j++)
                {
                    if(tabVoitures[j] != NULL
                       && tabVoitures[i]->getVitesseVoiture() > tabVoitures[j]->getVitesseVoiture())
                       // Voiture non NULL si la première est plus rapide que la seconde
                    {
                        bool collision = false;
                        int coteGauV1 = tabVoitures[i]->getPosX();
                        int coteDroV1 = coteGauV1 + tabVoitures[i]->getWidth();
                        int coteGauV2 = tabVoitures[j]->getPosX();
                        int coteDroV2 = coteGauV2 + tabVoitures[j]->getWidth();

                        // Si la deuxième voiture est devant la première il y a collision
                        if(coteGauV1 >= coteGauV2 && coteGauV1 <= coteDroV2)
                        {
                            collision = true;

                        }
                        else if(coteDroV1 >= coteGauV2 && coteDroV1 <= coteDroV2)
                        {
                            collision = true;
                        }

                        // La voiture double par la gauche ou ralentit si on est dans la première voie
                        if(collision )
                        {
                           if(tabVoitures[i]->getPosX() < route->getPosX() + route->getLargeurVoiePlateau())
                            {
                                if(tabVoitures[i]->getVitesseVoiture() > tabVoitures[j]->getVitesseVoiture())
                                tabVoitures[i]->setVitesseVoiture(tabVoitures[i]->getVitesseVoiture() - 1);
                            }
                            else
                            {
                                tabVoitures[i]->deplacer(-2,0);
                            }
                        }
                    }
                }
            }
        }
    }
}
