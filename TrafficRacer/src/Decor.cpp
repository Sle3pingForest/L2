#include "Decor.hpp"
using namespace std;

Decor::Decor()
{
    rectDecor.w = 0;
    rectDecor.h = 0;
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

void Decor::selectDecor(int type, int nb)
{
    if (type == 1) {
        rectImage.w = arbre_width;
        rectImage.h = arbre_heigth;
        rectImage.y = arbre_ligne;
        rectDecor.w = arbre_width;
        rectDecor.h = arbre_heigth;
    }
    rectImage.x = nb * arbre_width;
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

void Decor::afficher(SDL_Texture* texture)
{
    
    SDL_RenderCopy(pRenderer, texture, &rectImage, &rectDecor);
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
