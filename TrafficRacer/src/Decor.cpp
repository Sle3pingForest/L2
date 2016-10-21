#include "Decor.hpp"
using namespace std;

Decor::Decor() : Objet()
{
    objet.w = 0;
    objet.h = 0;
    objet.x = 0;
    objet.y = 0;
}

Decor::Decor(int w, int h, int x, int y) : Objet(w, h, x, y)
{
    objet.w = w;
    objet.h = h;
    objet.x = x;
    objet.y = y;
}

void Decor::selectDecor(int type, int nb)
{
    if (type == 1) {
        image.w = arbre_width;
        image.h = arbre_heigth;
        image.y = arbre_ligne;
        objet.w = arbre_width;
        objet.h = arbre_heigth;
    }
    image.x = nb * arbre_width;
}

Decor::~Decor()
{
    //dtor
}
