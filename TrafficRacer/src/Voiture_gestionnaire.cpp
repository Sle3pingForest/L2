#include "Voiture_gestionnaire.hpp"
std::ifstream infile;
ifstream fichier("autres/niveau2", ios::in);

Voiture_gestionnaire::Voiture_gestionnaire()
{
    for (int i = 0; i < nb_voiture; ++i)
    {
        tabVoitures[i] = NULL;
    }
    timerChargementFichier.start();
}

Voiture_gestionnaire::~Voiture_gestionnaire()
{
    for (int i = 0; i < nb_voiture; ++i)
    {
        if (tabVoitures[i] != NULL)
        {
            delete tabVoitures[i];
            tabVoitures[i] = NULL;
        }
    }
}

// Gère les déplacements, les suppressions de voitures et renvoie true si collision
bool Voiture_gestionnaire::gestion_voitures(int vitesse, SDL_Rect* rectVoitureJoueur)
{
    SDL_bool collision;
    SDL_Rect intersect;
    bool flagCollision = false;
    for (int i = 0; i < nb_voiture; ++i)
    {
        if (tabVoitures[i] != NULL)
        {
            if (tabVoitures[i]->isDead())
            {
                delete tabVoitures[i];
                tabVoitures[i] = NULL;
            }
            else
            {
                tabVoitures[i]->avancer(vitesse);
                collision = SDL_IntersectRect(rectVoitureJoueur, tabVoitures[i]->getRectCollision(), &intersect);
                if (collision)
                {
                    flagCollision = true;
                }
            }
        }
    }
    return flagCollision;
}

// Créer de nouvelles voitures et les positionner par rapport aux fichiers de niveaux
void Voiture_gestionnaire::chargement_voitures_fichier(Route* route)
{
    //infile.open("autres/niveau2");
    if (timerChargementFichier.getTicks() >1000)
    {
        string line;
        //getline(infile, line);
        fichier >> line;
        int j = 0;
        for( int i = 0 ; i < 4 ; ++i)
        {
            if(line[i] == '1' || line[i] == '2')
            {
                //On trouve une place libre dans le tableau de pointeurs de voitures
                while (tabVoitures[j] != NULL)
                {
                    ++j;
                }

                int position_x = route->getPosX() + i * route->getLargeurVoiePlateau() + rand()%10;
                tabVoitures[j] = new Voiture(position_x, -600, route->getLargeurVoiePlateau()-10, rand()%8);
                if(line[i] == '1')
                {
                    tabVoitures[j]->setVitesseVoiture(6);
                }
                else if (line[i] == '2')
                {
                    tabVoitures[j]->setVitesseVoiture(8);
                }
            }
        }
        infile.close();
        timerChargementFichier.start();
    }
}

void Voiture_gestionnaire::afficherVoitures(SDL_Texture* carsTexture)
{
    for(int i = 0 ; i < nb_voiture; i++)
    {
        if (tabVoitures[i] != NULL)
        {
            tabVoitures[i]->afficher(carsTexture);
            SDL_SetRenderDrawColor(pRenderer, 0, 0, 255, 150);
            tabVoitures[i]->afficherRectCollision();
        }
    }
}
