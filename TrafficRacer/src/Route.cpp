#include "Route.hpp"

using namespace std;

Route::Route() : Objet()
{
    objet.x = (SCREEN_WIDTH - objet.w)/2;
    objet.y = 0;
    objet.w = SCREEN_WIDTH*0.5;
    objet.h = SCREEN_HEIGHT;

    image.x = objet.x - image.w*0.04;
    image.y = 0;
    image.w = objet.w * 1.08;
    image.h = objet.w;
}

Route::~Route()
{
    //dtor
}

void Route::afficherVoies()
{
    SDL_SetRenderDrawColor(pRenderer, 0, 0, 255, 0);
    int positionVoie = objet.x;
    SDL_Rect ligne;
    ligne.x = positionVoie;
    ligne.h = objet.h;
    ligne.y = 0;
    ligne.w = 3;
    for ( int i = 0 ; i < 5 ; ++i)
    {
        ligne.x = positionVoie;
        SDL_RenderFillRect(pRenderer, &ligne);
        positionVoie += getLargeurVoie();
    }
}

void Route::afficher(SDL_Texture* texture)
{
    //Actualiser, à mettre dans une fonction
    objet.x = (SCREEN_WIDTH - objet.w)/2;
    objet.h = SCREEN_HEIGHT;
    image.x = objet.x - image.w*0.04;
    image.w = objet.w * 1.09;

    int nb_repetition_image = SCREEN_HEIGHT/image.h + 1;
    if(image.y > SCREEN_HEIGHT)
    {
        image.y -= image.h * (nb_repetition_image + 1);
    }
    SDL_RenderCopy(pRenderer, texture, NULL, &image);
    SDL_Rect test = image;
    for(int i = 0; i < nb_repetition_image; ++i)
    {
        test.y += image.h;
        if(test.y > SCREEN_HEIGHT)
        {
            test.y -= image.h * (nb_repetition_image + 1);
        }
        SDL_RenderCopy(pRenderer, texture, NULL, &test);
    }
}


void Route::deplacer(int vitesse)
{
    image.y += vitesse;
}

int Route::getLargeurVoie()
{
    return objet.w/4;
}
