//
//  main.cpp
//  SDL2
//
//  Created by Arnaud on 24/09/Ķ2016.
//  Copyright © 2016 Arnaud. All rights reserved.
//

#include "SDL_Tools.hpp"
#include "Partie.hpp"

SDL_Window *pWindow =NULL;
SDL_Renderer *pRenderer = NULL;

int SCREEN_WIDTH = 700;
int SCREEN_HEIGHT = 700;
int SCREEN_FPS = 50;

int main(int argc, const char * argv[])
{

    InitSDLEverything();
    Partie partie;
    Timer CPU;
    CPU.start();

    while (partie.continuer_partie())
    {
            partie.gestion_touches();
            partie.gestion_collisions();
            partie.chargement_voitures_fichier();
            partie.deplacements();
            partie.afficher();
            if(CPU.getTicks() >= 1000)
            {
                printf("FPS : %d\n", partie.FPS);
                partie.FPS = 0;
                CPU.start();
            }
            SDL_Delay(10);
    }

    SDL_DestroyRenderer(pRenderer);
    SDL_DestroyWindow(pWindow);

    SDL_Quit();

    return 0;
}
