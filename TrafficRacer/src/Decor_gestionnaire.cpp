#include "Decor_gestionnaire.hpp"

Decor_gestionnaire::Decor_gestionnaire()
{
    for (int i = 0; i < nb_decors; ++i)
    {
        tabDecors[i] = new Decor(100*(i/2), (i%2)*100, 1, i%3);
    }
}

Decor_gestionnaire::~Decor_gestionnaire()
{
    for (int i = 0; i < nb_decors; ++i)
    {
        delete tabDecors[i];
        tabDecors[i] = NULL;
    }
}

void Decor_gestionnaire::gestion(int vitesse)
{
    for (int i = 0; i < nb_decors; ++i)
    {
        if (tabDecors[i] != NULL)
        {
            if( tabDecors[i]->isDead())
            {
                delete tabDecors[i];
                tabDecors[i] = NULL;
                tabDecors[i] = new Decor(rand()%LEVEL_WIDTH, rand()%LEVEL_HEIGHT - LEVEL_HEIGHT, 1, rand()%9);
            }
            else
            {
                tabDecors[i]->deplacer(0, vitesse);
            }
        }
    }
}

void Decor_gestionnaire::afficherDecors(SDL_Texture* decorTexture)
{
    for(int i = 0 ; i < 30; i++)
    {
        if (tabDecors[i] != NULL)
        {
            tabDecors[i]->afficher(decorTexture);
        }
    }
}
