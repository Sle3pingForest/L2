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

void Decor::ChargerImage()
{
    SDL_Texture* texture = LoadBmpWithTransparency("/home/profil/scheffle5u/Téléchargements/arbre.bmp", 00, 255, 255);
    SDL_Rect dest = {rectDecor.x, rectDecor.y, rectDecor.w, rectDecor.h};
    SDL_RenderCopy(pRenderer,texture,NULL,&dest);
}

SDL_Rect* Decor::getRectDecor()
{
    return &rectDecor;
}

Decor::~Decor()
{
    //dtor
}
