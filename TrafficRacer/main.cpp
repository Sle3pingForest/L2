//
//  main.cpp
//  SDL2
//
//  Created by Arnaud on 24/09/Ķ2016.
//  Copyright © 2016 Arnaud. All rights reserved.
//

#include "Header.h"
#include "SDL_Init.hpp"
#include "Partie.h"

SDL_Window *pWindow =NULL;
SDL_Renderer *pRenderer = NULL;

int main(int argc, const char * argv[])
{

    InitSDLEverything();
    Partie partie;

    while (partie.continuer_partie())
    {
        partie.gestion_evenements();
        partie.afficher();
    }

    SDL_DestroyRenderer(pRenderer);
    SDL_DestroyWindow(pWindow);

    SDL_Quit();

    return 0;
}
