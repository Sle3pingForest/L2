#include "Decor.hpp"
#include "Route.hpp"
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
    pSprite = SDL_LoadBMP("/home/profil/scheffle5u/Téléchargements/arbre.bmp");
    if(pSprite == NULL)
    {
        cout<<SDL_GetError()<<endl;
    }
    SDL_SetColorKey(pSprite, SDL_TRUE, 0x00FFFF);
    SDL_Texture* pTexture = SDL_CreateTextureFromSurface(pRenderer,pSprite);
    if(pTexture == NULL)
    {
        cout<<SDL_GetError()<<endl;
    }
    //SDL_FreeSurface(pSprite);
    SDL_Rect dest = { 10 ,480/2 - pSprite->h/2, pSprite->w/2, pSprite->h/2};
    SDL_RenderCopy(pRenderer,pTexture,NULL,&dest);
}

SDL_Rect* Decor::getRectDecor()
{
    return &rectDecor;
}

Decor::~Decor()
{
    //dtor
}
