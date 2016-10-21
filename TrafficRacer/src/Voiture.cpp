#include "Voiture.hpp"
#include "Route.hpp"

Voiture::Voiture()
{
    objet.w = 48;
    objet.h = 80;
    objet.x = 0;
    objet.y = 0;

    image.x = 0;
    image.y = 0;
    image.w = 98;
    image.h = 214;
}

Voiture::Voiture(int x, int y, int w, int h) : Objet(w, h, x, y)
{
    objet.x = x;
    objet.y = y;
    objet.w = w;
    objet.h = h;
}

Voiture::~Voiture()
{
    //dtor
}
