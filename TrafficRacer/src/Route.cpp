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

    ligne.h = road.h;
    ligne.w = 2;
    ligne.x = SCREEN_WIDTH/2 + getWeightRoad()/4;
    ligne.y = 0;

    ligne2.h = road.h;
    ligne2.w = 2;
    ligne2.x = SCREEN_WIDTH/2 - getWeightRoad()/4;
    ligne2.y = 0;

    ligne3.h = road.h;
    ligne3.w = 2;
    ligne3.x = SCREEN_WIDTH/2 ;
    ligne3.y = 0;

    SDL_SetRenderDrawColor(pRenderer, 0, 0, 255, 255);
    SDL_RenderFillRect(pRenderer, getRectRoute());

    SDL_SetRenderDrawColor(pRenderer, 0, 0, 0, 0);
    SDL_RenderFillRect(pRenderer, &ligne);
    SDL_RenderFillRect(pRenderer, &ligne2);
    SDL_RenderFillRect(pRenderer, &ligne3);

}

SDL_Rect* Route::getRectRoute()
{
    return &road;
}

int Route::getWeightRoad()
{
    return road.w;
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
