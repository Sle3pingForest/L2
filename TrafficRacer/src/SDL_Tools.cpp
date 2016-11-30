#include "SDL_Tools.hpp"

bool InitSDL()
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0 ) {
        fprintf(stderr,"Échec de l'initialisation de la SDL (%s)\n",SDL_GetError());
        return false;
    }
    pWindow = SDL_CreateWindow("TrafficRacer", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_RESIZABLE);
    if( !pWindow ) {
        fprintf(stderr,"Erreur de création de la fenêtre: %s\n",SDL_GetError());
        return false;
    }
    pRenderer =  SDL_CreateRenderer( pWindow, -1, SDL_RENDERER_ACCELERATED );
    if( !pRenderer ) {
        fprintf(stderr, "Échec de la création du rendu: %s\n", SDL_GetError());
        return false;
    }
    SDL_SetRenderDrawBlendMode(pRenderer, SDL_BLENDMODE_BLEND);
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
