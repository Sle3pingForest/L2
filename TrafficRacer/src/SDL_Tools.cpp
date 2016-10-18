//
//  SDL_Init.cpp
//  SDL2
//
//  Created by Arnaud on 24/09/2016.
//  Copyright © 2016 Arnaud. All rights reserved.
//

#include "SDL_Tools.hpp"
using namespace std;

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

SDL_Texture* LoadBmpWithTransparency(const char* emplacement, Uint8 redTransparency, Uint8 greenTransparency, Uint8 blueTransparency)
{
    SDL_Surface *loadedImage = NULL;
    SDL_Texture *texture = NULL;

    loadedImage = SDL_LoadBMP(emplacement);

    if(loadedImage != NULL)
    {
        Uint32 colorkey = SDL_MapRGB( loadedImage->format, redTransparency, greenTransparency, blueTransparency);
        SDL_SetColorKey(loadedImage, SDL_TRUE, colorkey);
        texture = SDL_CreateTextureFromSurface(pRenderer, loadedImage);
        SDL_FreeSurface(loadedImage);
        return texture;
    }
    else
    {
        fprintf(stderr, "Échec du chargement de l'image: %s\n", SDL_GetError());
        return NULL;
    }
}
