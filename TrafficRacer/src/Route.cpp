#include "Route.hpp"

using namespace std;

Route::Route() : Objet()
{
    objet.w = SCREEN_WIDTH*0.5;
    objet.h = SCREEN_HEIGHT;
    objet.x = (SCREEN_WIDTH - objet.w)/2;
    objet.y = 0;

    image = objet;
    image.h = 300;
}

Route::Route(int w, int h, int x, int y) : Objet(w, h, x, y)
{
    objet.w = w;
    objet.h = h;
    objet.x = x;
    objet.y = y;

    image = objet;
    image.h = 300;
}

Route::~Route()
{
    //dtor
}

void Route::afficherVoies()
{
    SDL_SetRenderDrawColor(pRenderer, 0, 0, 255, 255);
    int positionVoie = SCREEN_WIDTH/2 - 2* getLargeurVoie();
    SDL_Rect ligne;
    ligne.x = positionVoie;
    ligne.h = objet.h;
    ligne.y = 0 ;
    ligne.w = 2 ;
    for ( int i = 0 ; i < 5 ; ++i)
    {
        ligne.x = positionVoie;
        SDL_RenderFillRect(pRenderer, &ligne);
        positionVoie += getLargeurVoie();
    }
}

void Route::afficher(SDL_Texture* texture)
{

    int nb_repetition_image = 3;
    if(image.y > SCREEN_HEIGHT)
    {
        image.y -= image.h * (nb_repetition_image + 1);
    }
    SDL_RenderCopy(pRenderer, texture, NULL, &image);
    SDL_Rect test = image;
    for(int i = 0; i < 3; ++i)
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
