#include "Voiture.hpp"
#include "Route.hpp"

Voiture::Voiture()
{
    rectCar.w = 40;
    rectCar.h = 80;
    couleur = 0;
}

Voiture::Voiture(int w, int h)
{
    rectCar.w = w;
    rectCar.h = h;
    couleur = 0;
}

void Voiture::placer(int x, int y)
{
    rectCar.x = x;
    rectCar.y = y;
}

void Voiture::deplacer( int x, int y)
{
    rectCar.x += x;
    rectCar.y += y;
}

void Voiture::AfficherVoiture()
{
    SDL_SetRenderDrawColor(pRenderer, 255, 255, 0, 0);
    SDL_RenderFillRect(pRenderer, getRectCar());
}

SDL_Rect* Voiture::getRectCar()
{
    return &rectCar;
}

int Voiture::getCouleur()
{
    return couleur;
}

void Voiture::setCouleur( int code)
{
    this->couleur = code;
}

void Voiture::setWeight(int tailleW)
{
    rectCar.w = tailleW;
}

void Voiture::setHeight( int tailleH)
{
    rectCar.h = tailleH;
}

int Voiture::getPosX()
{
    return rectCar.x;
}

int Voiture::getPosY()
{
    return rectCar.y;
}

int Voiture::getCarWidth()
{
    return rectCar.w;
}

int Voiture::getCarHeight()
{
    return rectCar.h;
}

Voiture::~Voiture()
{
    //dtor
}
