#include "Route.hpp"

Road::Road()
{
    //ctor
}

#include "drawing.hpp"
#include <math.h>
#include "Decor.hpp"
#include "Voiture.hpp"

void CreateRoad()
{
    SDL_Rect road;
    road.w = SCREEN_WIDTH*0.6;
    road.h = SCREEN_HEIGHT;
    road.x = (SCREEN_WIDTH - road.w)/2;
    road.y = 0;
    SDL_SetRenderDrawColor(pRenderer, 0, 0, 255, 255);
    SDL_RenderFillRect(pRenderer, &road);
}

Road::~Road()
{
    //dtor
}
