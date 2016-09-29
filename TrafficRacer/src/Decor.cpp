#include "Decor.hpp"
#include "drawing.hpp"

Decor::Decor()
{
    rectDecor.w = 50;
    rectDecor.h = 50;
    rectDecor.x = 0;
    rectDecor.y = 0;
}

Decor::Decor(int w, int h, int x, int y)
{
    rectDecor.w = w;
    rectDecor.h = h;
    rectDecor.x = x;
    rectDecor.y = y;
}

void Decor::placer(int x, int y)
{
    rectDecor.x = x;
    rectDecor.y = y;
}

void Decor::CreateDecor()
{
    int x = rand()%50;
    int y = rand()%SCREEN_HEIGHT;
    placer(x,y);
    SDL_RenderFillRect(pRenderer, getRectDecor());
    SDL_SetRenderDrawColor(pRenderer, 0, 255, 0, 255);

}

SDL_Rect* Decor::getRectDecor()
{
    return &rectDecor;
}

Decor::~Decor()
{
    //dtor
}
