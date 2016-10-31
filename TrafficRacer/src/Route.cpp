#include "Route.hpp"

using namespace std;

Route::Route()
{
    positionPlateau.w = LEVEL_WIDTH * 0.25;
    positionPlateau.h = LEVEL_HEIGHT;
    positionPlateau.x = (LEVEL_WIDTH - positionPlateau.w)/2;
    positionPlateau.y = 0;
    
    position_y = 0;
}

Route::~Route()
{
    //dtor
}

void Route::afficherVoies()
{
    SDL_Rect ligne = calculerPosFenetre();
    ligne.w = 3;
    
    for ( int i = 0 ; i < 5 ; ++i)
    {
        SDL_RenderFillRect(pRenderer, &ligne);
        ligne.x += getLargeurVoieFenetre();
    }
}

void Route::afficher(SDL_Texture* texture)
{
    
    int nbRepetitionImage = 3;
    positionPlateau.h = positionPlateau.w;
    if (position_y > LEVEL_HEIGHT)
    {
        position_y -= positionPlateau.h * nbRepetitionImage;
    }
    
    positionPlateau.y = position_y;
    
    for ( int i = 0 ; i < 3 ; ++i)
    {
        SDL_Rect positionFenetre = calculerPosFenetre();
        SDL_RenderCopy(pRenderer, texture, NULL, &positionFenetre);
        positionPlateau.y += positionPlateau.h;
        if (positionPlateau.y > 0)
        {
            positionPlateau.y -= (positionPlateau.h * nbRepetitionImage);
        }
    }

    
    // Replace les position comme au début
    positionPlateau.h = LEVEL_HEIGHT;
    positionPlateau.y = 0;
}


void Route::deplacer(int vitesse)
{
    position_y += vitesse;
}

int Route::getLargeurVoiePlateau()
{
    return (positionPlateau.w/4);
}

int Route::getLargeurVoieFenetre()
{
    return (positionPlateau.w/4)*echelle;
}
