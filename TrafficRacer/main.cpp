//
//  main.cpp
//  SDL2
//
//  Created by Arnaud on 24/09/Ķ2016.
//  Copyright © 2016 Arnaud. All rights reserved.
//

#include "Header.h"
#include "SDL_Init.hpp"
#include "Decor.hpp"

SDL_Window *pWindow =NULL;
SDL_Renderer *pRenderer = NULL;

int main(int argc, const char * argv[])
{
    bool quit = false;
    SDL_Event event;

    //Constantes pour compteur FPS
    const int FPS = 30;
    Uint32 start;

    //Varriables couleurs
    Uint8 rouge = 0;
    Uint8 vert = 0;
    Uint8 bleu = 0;

    InitEverything();

    while (!quit)
    {
        start = SDL_GetTicks();
        // Gestion des événements
        while( SDL_PollEvent( &event ) != 0 )
        {
            if (event.type == SDL_QUIT) {
                quit = true;

            }
            // Les touches
            else if( event.type == SDL_KEYDOWN )
            {
                switch( event.key.keysym.sym )
                {
                    case SDLK_UP:
                        if(vert < (255-20))
                            vert += 20;
                        else
                            vert = 255;
                        break;

                    case SDLK_DOWN:
                        if(vert > 20)
                            vert -= 20;
                        else
                            vert = 0;
                        break;

                    case SDLK_LEFT:
                        if(rouge > 20)
                            rouge -= 20;
                        else
                            rouge = 0;
                        break;

                    case SDLK_RIGHT:
                        if(rouge < (255-20))
                            rouge += 20;
                        else
                            rouge = 255;
                        break;

                    default:
                        break;
                }
            }

        }
        SDL_SetRenderDrawColor(pRenderer, 00, 00, 00, 255);
        SDL_RenderClear(pRenderer);
        SDL_SetRenderDrawColor(pRenderer, rouge, vert, bleu, 255);
        drawGame();
        //drawEchiquier();
        //drawTriangle();
        SDL_RenderPresent(pRenderer);

        //Calcul du temps à attendre pour FPS
        if(1000/FPS > SDL_GetTicks()-start)
        {
            SDL_Delay(1000/FPS-(SDL_GetTicks()-start));
        }

    }
    SDL_DestroyRenderer(pRenderer);
    SDL_DestroyWindow(pWindow);

    SDL_Quit();

    return 0;
}
