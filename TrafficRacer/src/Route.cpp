#include "Route.hpp"

using namespace std;

Route::Route()
{
    positionPlateau.w = LEVEL_WIDTH * 0.25;
    positionPlateau.h = LEVEL_HEIGHT;
    positionPlateau.x = (LEVEL_WIDTH - positionPlateau.w)/2;
    positionPlateau.y = 0;

    position_y = 0;

    image = positionPlateau;
    image.h = image.w;
}

Route::~Route()
{
    //dtor
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
    static const int nb_repetition_image = 4;
    if (image.y > LEVEL_HEIGHT)
    {
        image.y -= (image.h * nb_repetition_image) - (1 * nb_repetition_image);
    }
    int position = image.y;

    SDL_Rect positionFenetre;
    //Calcul du déplacement
    positionFenetre.x = (image.x * echelle) - camera.x;
    //Calcul du redimensionnement
    positionFenetre.w = image.w * echelle;
    positionFenetre.h = image.h * echelle;
    // Ajouter le décalage de la rambarde

    for (int i = 0 ; i < nb_repetition_image ; i++)
    {
        position = position + (image.h * i) - 1;
        if (position > LEVEL_HEIGHT)
        {
            position -= (image.h * nb_repetition_image) - (1 * nb_repetition_image);
        }
        positionFenetre.y = (position * echelle) - camera.y;
        SDL_RenderCopy(pRenderer, texture, NULL, &positionFenetre);
    }
}

void Route::deplacer(int vitesse)
{
    image.y += vitesse;
}

int Route::getLargeurVoiePlateau()
{
    return (positionPlateau.w / 4);
}

int Route::getLargeurVoieFenetre()
{
    return (positionPlateau.w / 4) * echelle;
}
