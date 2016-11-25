#include "Route.hpp"

Route::Route()
{
    positionPlateau.w = LEVEL_WIDTH * 0.25;
    positionPlateau.h = LEVEL_HEIGHT;
    positionPlateau.x = (LEVEL_WIDTH - positionPlateau.w)/2;
    positionPlateau.y = 0;

    position_y = 0;

    image = positionPlateau;
    image.h = image.w;
    image.y = -image.h;
}

void Route::afficherVoies()
{
    SDL_Rect ligne = calculerPosFenetre(&positionPlateau);
    ligne.w = 3;

    for ( int i = 0 ; i < 5 ; ++i)
    {
        SDL_RenderFillRect(pRenderer, &ligne);
        ligne.x += getLargeurVoieFenetre();
    }
}

void Route::afficherDefilement(SDL_Texture* texture)
{
    //Calcul du nombre de répétitions d'image nécéssaire
    static const int nb_repetition = LEVEL_HEIGHT/image.h +1;
    
    //On affiche une fois l'image
    if (image.y >= 0)
    {
        image.y -= (image.h);
    }
    SDL_Rect positionFenetre = calculerPosFenetre(&image);
    SDL_RenderCopy(pRenderer, texture, NULL, &positionFenetre);
    int tmp = image.y;
    
    // Puis on la duplique plusieurs fois en dessous
    for (int i = 0; i < nb_repetition; ++i) {
        image.y += image.h-2;
        positionFenetre = calculerPosFenetre(&image);
        SDL_RenderCopy(pRenderer, texture, NULL, &positionFenetre);
    }
    image.y = tmp;
}

void Route::deplacer(int pixels)
{
    image.y += pixels;
}

int Route::getLargeurVoiePlateau()
{
    return (positionPlateau.w / 4);
}

int Route::getLargeurVoieFenetre()
{
    return (positionPlateau.w / 4) * echelle;
}
