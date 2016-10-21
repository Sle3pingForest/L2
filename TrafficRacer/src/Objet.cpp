#include "Objet.hpp"

Objet::Objet() // constructeur sans parametre
{
    objet.x ;
    objet.y ;
    objet.w ;
    objet.h ;
}

Objet::Objet( int w, int h)
{
    objet.x;
    objet.y ;
    objet.w = w;
    objet.h = h;
}

Objet::Objet( int w, int h, int x, int y)
{
    objet.x = x;
    objet.y = y;
    objet.w = w;
    objet.h = h;
}

void Objet::placer(int x, int y)
{
    objet.x = x;
    objet.y = y;
}

void Objet::deplacer( int x, int y)
{
    objet.x += x;
    objet.y += y;
}

void Objet::afficher(SDL_Texture* texture)
{
    SDL_RenderCopy(pRenderer, texture, &image, &objet);
}

void Objet::afficherObjet()
{
    SDL_RenderFillRect(pRenderer, &objet);
}

int Objet::getPosX()
{
    return objet.x;
}

int Objet::getPosY()
{
    return objet.y;
}

int Objet::getWidth()
{
    return objet.w;
}

int Objet::getHeight()
{
    return objet.h;
}

void Objet::setPosX(int x)
{
    objet.x = x;
}

void Objet::setPosY(int y)
{
    objet.y = y;
}

void Objet::setWidth(int w)
{
    objet.w = w;
}

void Objet::setHeight(int h)
{
    objet.h = h;
}
SDL_Rect* Objet::getObjet()
{
    return &objet;
}

Objet::~Objet()
{
    //dtor
}
