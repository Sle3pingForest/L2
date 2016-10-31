#include "Decor.hpp"
using namespace std;

Decor::Decor() : Objet()
{
    objet.w = 0;
    objet.h = 0;
    objet.x = 0;
    objet.y = 0;
}

Decor::Decor(int x, int y)
{
    positionPlateau.x = x;
    positionPlateau.y = y;
}

void Decor::selectDecor(int type, int nb)
{
    if (type == 1) {
        image.w = arbre_width;
        image.h = arbre_heigth;
        image.x = nb * arbre_width;
        image.y = arbre_ligne;
        positionPlateau.w = arbre_width;
        positionPlateau.h = arbre_heigth;
    }
}

bool Decor::isDead()
{
    if (positionPlateau.y > LEVEL_HEIGHT) {
        return true;
    }
    return false;
}

Decor::~Decor()
{
    //dtor
}
