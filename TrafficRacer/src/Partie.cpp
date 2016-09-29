#include <SDL2/SDL.h>
#include "Partie.h"
#include "Header.h"
#include "drawing.hpp"
#include "Voiture.h"


Partie::Partie()
{
    jouer = true;
    voiture_joueur.placer(SCREEN_WIDTH/2, SCREEN_HEIGHT-80);
}

Partie::~Partie()
{
    //dtor
}

void Partie::gestion_evenements()
{
    SDL_Event event;
    while( SDL_PollEvent( &event ) != 0 )
    {
        //Fermer la fenêtre
        if (event.type == SDL_QUIT)
        {
            jouer = false;

        }
        // Les touches
        else if( event.type == SDL_KEYDOWN )
        {
            switch( event.key.keysym.sym )
            {
            case SDLK_UP:
                    break;

            case SDLK_DOWN:
                break;

            case SDLK_LEFT:
                voiture_joueur.deplacer(-25);
                break;

            case SDLK_RIGHT:
                voiture_joueur.deplacer(+25);
                break;

            default:
                break;
            }
        }

    }
}

void Partie::afficher()
{
    SDL_SetRenderDrawColor(pRenderer, 0, 0, 0, 255);
    SDL_RenderClear(pRenderer);
    voiture_joueur.AfficherVoiture();
    SDL_RenderPresent(pRenderer);
}

bool Partie::continuer_partie()
{
    return jouer;
}
