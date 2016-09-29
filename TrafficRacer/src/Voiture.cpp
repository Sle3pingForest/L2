#include "Voiture.h"
#include "drawing.hpp"

Voiture::Voiture()
{
    rectCar.w = 20;
    rectCar.h = 40;
    rectCar.x = SCREEN_WIDTH/2;
    rectCar.y = SCREEN_HEIGHT;
}

Voiture::Voiture(int w, int h)
{
    rectCar.w = w;
    rectCar.h = h;
    rectCar.x = SCREEN_WIDTH/2;
    rectCar.y = SCREEN_HEIGHT;

}

void Voiture::placer(int x, int y)
{
    rectCar.x = x;
    rectCar.y = y;
}

void Voiture::CreateCar()
{
    Voiture car;
    car.placer(SCREEN_WIDTH/2, SCREEN_HEIGHT -80);
    SDL_RenderFillRect(pRenderer, car.getRectCar());
    SDL_SetRenderDrawColor(pRenderer, 0, 0, 0, 0);

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
