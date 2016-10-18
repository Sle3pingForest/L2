#include "Voiture.hpp"
#include "Route.hpp"

Voiture::Voiture()
{
    rectCar.w = 48;
    rectCar.h = 80;
    rectCar.x = 0;
    rectCar.y = 0;
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
    SDL_RenderFillRect(pRenderer, getRectCar());
}

void Voiture::afficher(SDL_Texture* texture)
{
    SDL_Rect rectImage;
    rectImage.x = 0;
    rectImage.y = 0;
    rectImage.w = 98;
    rectImage.h = 214;
    SDL_RenderCopy(pRenderer, texture, &rectImage, &rectCar);
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
