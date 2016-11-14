//
//  main.cpp
//  SDL2
//
//  Created by Arnaud on 24/09/Ķ2016.
//  Copyright © 2016 Arnaud. All rights reserved.
//

#include "Partie.hpp"
#include "Joueur.hpp"

int main(int argc, const char * argv[])
{


    Joueur player;
    //player.setName();

    InitSDLEverything();
    Partie partie;
    partie.play();
    Timer CPU;
    CPU.start();

    while (player.getName() !="" && partie.continuer_partie())
    {
        partie.play();
        if(CPU.getTicks() >= 1000)
        {
            //printf("FPS : %d\n", partie.FPS);
            partie.FPS = 0;
            CPU.start();
        }
        SDL_Delay(10);
    }

    SDL_DestroyRenderer(pRenderer);
    SDL_DestroyWindow(pWindow);

    SDL_Quit();

    partie.~Partie();
    return 0;
}
