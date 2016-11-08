//
//  main.cpp
//  SDL2
//
//  Created by Arnaud on 24/09/Ķ2016.
//  Copyright © 2016 Arnaud. All rights reserved.
//

#include "SDL_Tools.hpp"
#include "Partie.hpp"

int main(int argc, const char * argv[])
{

    InitSDLEverything();
    Partie partie;
    Timer CPU;
    CPU.start();

    while (partie.continuer_partie())
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

    return 0;
}
