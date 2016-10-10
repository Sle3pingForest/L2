#include "Decor.hpp"
#include "Route.hpp"
#include "SDL_Init.hpp"
using namespace std;

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

void Decor::afficher(int w, int h, SDL_Texture* texture)
{
    rectDecor.w = w;
    rectDecor.h = h;
    SDL_RenderCopy(pRenderer,texture,NULL,&rectDecor);
}

void Decor::deplacer(int x, int y)
{
    rectDecor.x += x;
    rectDecor.y += y;
}

Decor::~Decor()
{
    //dtor
}
