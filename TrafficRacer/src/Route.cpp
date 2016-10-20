#include "Route.hpp"

using namespace std;

Route::Route()
{
    road.w = SCREEN_WIDTH*0.5;
    road.h = SCREEN_HEIGHT;
    road.x = (SCREEN_WIDTH - road.w)/2;
    road.y = 0;

    roadPortionRender = road;
    roadPortionRender.h = 300;
}


void Route::afficherVoies()
{
    SDL_SetRenderDrawColor(pRenderer, 0, 0, 255, 255);
    int positionVoie = SCREEN_WIDTH/2 - 2* getLargeurVoie();
    SDL_Rect ligne;
    ligne.x = positionVoie;
    ligne.h = road.h;
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
    if(roadPortionRender.y > SCREEN_HEIGHT)
    {
        roadPortionRender.y -= roadPortionRender.h * (nb_repetition_image + 1);
    }
    SDL_RenderCopy(pRenderer, texture, NULL, &roadPortionRender);
    SDL_Rect test = roadPortionRender;
    for(int i = 0; i < 3; ++i)
    {
        test.y += roadPortionRender.h;
        if(test.y > SCREEN_HEIGHT)
        {
            test.y -= roadPortionRender.h * (nb_repetition_image + 1);
        }
        SDL_RenderCopy(pRenderer, texture, NULL, &test);
    }
}

void Route::deplacer(int vitesse)
{
    roadPortionRender.y += vitesse;
}

SDL_Rect* Route::getRectRoute()
{
    return &road;
}

int Route::getWeightRoad()
{
    return road.w;
}
int Route::getPositionXRoad()
{
    return road.x;
}

int Route::getLargeurVoie()
{
    return road.w/4;
}

int Route::getHeightRoad()
{
    return road.h;
}

Route::~Route()
{
    //dtor
}
