#include "Voiture.h"
#include "drawing.hpp"

Voiture::Voiture()
{
    rectCar.w = 20;
    rectCar.h = 40;
}

Voiture::Voiture(int w, int h)
{
    rectCar.w = w;
    rectCar.h = h;
}

void Voiture::placer(int x, int y)
{
    rectCar.x = x;
    rectCar.y = y;
}

void Voiture::deplacer( int mouvement)
{
    rectCar.x += mouvement;
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

Voiture::~Voiture()
{
    //dtor
}
