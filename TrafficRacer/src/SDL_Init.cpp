//
//  SDL_Init.cpp
//  SDL2
//
//  Created by Arnaud on 24/09/2016.
//  Copyright © 2016 Arnaud. All rights reserved.
//


//Fonction qui initialise la SDL avec gestion d'érreurs
//La gestion d'érreur est en pratique peu utilisée...

#include "SDL_Init.hpp"
extern SDL_Window *pWindow;
extern SDL_Renderer *pRenderer;

bool InitSDLEverything()
{
    if( !InitSDL() )
        return false;

    if( !CreateWindowAndRenderer() )
        return false;
    
    SDL_SetWindowTitle(pWindow,"TrafficRacer");

    return true;
}

bool InitSDL()
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0 )
    {
        fprintf(stderr,"Échec de l'initialisation de la SDL (%s)\n",SDL_GetError());
        return false;
    }
    return true;
}

bool CreateWindow()
{
    pWindow = SDL_CreateWindow("Hello World", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

    if( !pWindow )
    {

        fprintf(stderr,"Erreur de création de la fenêtre: %s\n",SDL_GetError());
        return false;

    }
    return true;
}

bool CreateRenderer()
{
    pRenderer =  SDL_CreateRenderer( pWindow, -1, SDL_RENDERER_ACCELERATED);
    if( !pRenderer )
    {
        fprintf(stderr, "Échec de la création du rendu: %s\n", SDL_GetError());
        return false;
    }
    return true;
}

bool CreateWindowAndRenderer()
{
    if( SDL_CreateWindowAndRenderer(SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN, &pWindow, &pRenderer) ) //0 = succès
    {
        fprintf(stderr, "Échec de la création de la fenêtre et du rendu: %s\n", SDL_GetError());
        return false;
    }
    return true;
}
