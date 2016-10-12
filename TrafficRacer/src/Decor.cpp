#include "Decor.hpp"
using namespace std;

Decor::Decor()
{
    rectDecor.w = 150;
    rectDecor.h = 150;
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

void Decor::afficher(SDL_Texture* texture)
{
    SDL_RenderCopy(pRenderer,texture,NULL,&rectDecor);
}

void Decor::placer(int x, int y)
{
    rectDecor.x = x;
    rectDecor.y = y;
}

void Decor::deplacer(int x, int y)
{
    rectDecor.x += x;
    rectDecor.y += y;
}

int Decor::getPosX()
{
    return rectDecor.x;
}

int Decor::getPosY()
{
    return rectDecor.y;
}

int Decor::getDecorWidth()
{
    return rectDecor.w;
}

int Decor::getDecorHeight()
{
    return rectDecor.h;
}

Decor::~Decor()
{
    //dtor
}
