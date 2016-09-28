#include "Decor.h"

Decor::Decor()
{
    rectDecor.w = 50;
    rectDecor.h = 50;
    rectDecor.x = 0;
    rectDecor.y = 0;
}

void Decor::placer(int x, int y)
{
    rectDecor.x = x;
    rectDecor.y = y;
}

Decor::~Decor()
{
    //dtor
}
