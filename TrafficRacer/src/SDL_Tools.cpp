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

void afficherChiffre(SDL_Texture* texture, char chiffre, int HauteurPolice, int PosX, int PosY) {
    int intChiffre = chiffre - 48;
    SDL_Rect dest;
    dest.x = PosX;
    dest.y = PosY;
    dest.h = HauteurPolice;
    dest.w = HauteurPolice / 1.6;
    
    SDL_Rect selection;
    selection.y = 0;
    selection.w = 90;
    selection.h = 144;
    selection.x = (intChiffre * 91) + intChiffre;
    
    SDL_RenderCopy(pRenderer, texture, &selection, &dest);
}

void afficherNombre(SDL_Texture* texture, int nombre, int HauteurPolice, int PosX, int PosY)
{
    int unite = nombre % 10;
    int dizaine = nombre / 10 % 10;
    int centaine = nombre / 100 % 10;
    int milier = nombre / 1000 % 10;
    
    int largeur = HauteurPolice / 1.6;
    
    afficherChiffre(texture, milier,HauteurPolice,PosX,PosY);
    afficherChiffre(texture, centaine,HauteurPolice,PosX+largeur+5,PosY);
    afficherChiffre(texture, dizaine,HauteurPolice,PosX+(2*(largeur+5)),PosY);
    afficherChiffre(texture, unite,HauteurPolice,PosX+(3*(largeur+5)),PosY);
}
