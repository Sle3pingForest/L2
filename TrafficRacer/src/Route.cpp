#include "Route.hpp"
#include <math.h>
#include "Decor.hpp"
#include "Voiture.hpp"

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
}

SDL_Rect* Route::getRectRoute()
{
    return &road;
}

Route::~Route()
{
    //dtor
}
