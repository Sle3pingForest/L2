#include "Route.hpp"
#include <math.h>
#include "Decor.hpp"
#include "Voiture.hpp"
using namespace std;

Route::Route()
{
    road.w = SCREEN_WIDTH*0.6;
    road.h = SCREEN_HEIGHT;
    road.x = (SCREEN_WIDTH - road.w)/2;
    road.y = 0;
}


void Route::AfficherRoute()
{
    SDL_SetRenderDrawColor(pRenderer, 0, 0, 255, 255);
    SDL_RenderFillRect(pRenderer, getRectRoute());

    int positionVoie = SCREEN_WIDTH/2 - 2* getLargeurVoie();
    SDL_SetRenderDrawColor(pRenderer, 0, 0, 0, 0);
    for ( int i = 0 ; i < 4 ; ++i)
    {
        SDL_Rect ligne;
        tabVoie[i] = ligne;
        tabVoie[i].x = positionVoie;
        tabVoie[i].h = road.h;
        tabVoie[i].y = 0 ;
        tabVoie[i].w = 2 ;
        SDL_RenderFillRect(pRenderer, &tabVoie[i]);
        positionVoie += getLargeurVoie();

    }

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
