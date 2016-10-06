#include <SDL2/SDL.h>
#include "Partie.h"
#include "Header.h"
#include "drawing.hpp"
#include "Voiture.h"


Partie::Partie()
{
    jouer = true;
    voiture_joueur.placer(SCREEN_WIDTH/2, SCREEN_HEIGHT-80);
    tabVoiture[0].placer(100, 100);
    tabVoiture[1].placer(200, 100);
    tabVoiture[2].placer(400, 100);
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
                voiture_joueur.deplacer(-25, 0);
                break;

            case SDLK_RIGHT:
                voiture_joueur.deplacer(+25, 0);
                break;

            default:
                break;
            }
        }

    }
}

void Partie::afficher()
{
    const int FPS = 60;
    Uint32 start;
    start = SDL_GetTicks();

    SDL_SetRenderDrawColor(pRenderer, 0, 0, 0, 255);
    SDL_RenderClear(pRenderer);

    if(tabVoiture[0].getPosY() > SCREEN_HEIGHT)
        tabVoiture[0].placer(rand() %SCREEN_WIDTH,0);
    tabVoiture[0].deplacer(0, 4);
    tabVoiture[0].AfficherVoiture();

    if(tabVoiture[1].getPosY() > SCREEN_HEIGHT)
        tabVoiture[1].placer(rand() %SCREEN_WIDTH,0);
    tabVoiture[1].deplacer(0, 8);
    tabVoiture[1].AfficherVoiture();

    if(tabVoiture[2].getPosY() > SCREEN_HEIGHT)
        tabVoiture[2].placer(rand() %SCREEN_WIDTH,0);
    tabVoiture[2].deplacer(0, 9);
    tabVoiture[2].AfficherVoiture();

    voiture_joueur.AfficherVoiture();
    SDL_RenderPresent(pRenderer);

    //Calcul du temps à attendre les FPS
    if(1000/FPS > SDL_GetTicks()-start)
    {
        SDL_Delay(1000/FPS-(SDL_GetTicks()-start));
    }
}

bool Partie::continuer_partie()
{
    return jouer;
}
