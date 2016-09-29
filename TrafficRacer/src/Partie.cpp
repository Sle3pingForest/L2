#include <SDL2/SDL.h>
#include "Partie.h"
#include "Header.h"


Partie::Partie()
{
    jouer = true;
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
                break;

            case SDLK_RIGHT:
                break;

            default:
                break;
            }
        }

    }
}

void Partie::afficher()
{
    SDL_SetRenderDrawColor(pRenderer, 255, 255, 255, 255);
    SDL_RenderClear(pRenderer);
    SDL_RenderPresent(pRenderer);
}

bool Partie::continuer_partie()
{
    return jouer;
}
