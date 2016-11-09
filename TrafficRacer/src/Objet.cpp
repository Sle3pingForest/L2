#include "Objet.hpp"

Objet::Objet() // constructeur sans parametre
{
    positionPlateau.x = 0;
    positionPlateau.y = 0;
    positionPlateau.w = 0;
    positionPlateau.h = 0;

    image.x = 0;
    image.y = 0;
    image.w = 0;
    image.h = 0;
}

Objet::Objet( int w, int h)
{
    positionPlateau.w = w;
    positionPlateau.h = h;
}

Objet::Objet( int x, int y, int w, int h)
{
    positionPlateau.x = x;
    positionPlateau.y = y;
    positionPlateau.w = w;
    positionPlateau.h = h;
}

void Objet::placer(int x, int y)
{
    positionPlateau.x = x;
    positionPlateau.y = y;
}

void Objet::deplacer( int x, int y)
{
    positionPlateau.x += x;
    positionPlateau.y += y;
}

void Objet::afficher(SDL_Texture* texture)
{
    SDL_Rect positionFenetre = calculerPosFenetre(&positionPlateau);
    SDL_RenderCopy(pRenderer, texture, &image, &positionFenetre);
}

void Objet::afficherRectObjet()
{
    SDL_Rect positionFenetre = calculerPosFenetre(&positionPlateau);
    SDL_RenderFillRect(pRenderer, &positionFenetre);
}

void Objet::calculerLargeur()
{
    positionPlateau.w = image.w * positionPlateau.h / image.h;
}

void Objet::calculerHauteur()
{
    positionPlateau.h = image.h * positionPlateau.w / image.w;
}

SDL_Rect Objet::calculerPosFenetre(SDL_Rect* RectACalculer)
{
    SDL_Rect positionFenetre;
    //Calcul du déplacement
    positionFenetre.x = (RectACalculer->x * echelle) - camera.x;
    positionFenetre.y = (RectACalculer->y * echelle) - camera.y;
    //Calcul du redimensionnement
    positionFenetre.w = RectACalculer->w * echelle;
    positionFenetre.h = RectACalculer->h * echelle;
    return positionFenetre;
}

int Objet::calculerHauteurDansFenetre()
{
    return positionPlateau.h * echelle;
}

int Objet::calculerLargeurDansFenetre()
{
    return positionPlateau.w * echelle;
}

int Objet::getPosX()
{
    return positionPlateau.x;
}

int Objet::getPosY()
{
    return positionPlateau.y;
}

int Objet::getWidth()
{
    return positionPlateau.w;
}

int Objet::getHeight()
{
    return positionPlateau.h;
}

SDL_Rect* Objet::getObjet()
{
    return &positionPlateau;
}

void Objet::setPosX(int x)
{
    positionPlateau.x = x;
}

void Objet::setPosY(int y)
{
    positionPlateau.y = y;
}

void Objet::setWidth(int w)
{
    positionPlateau.w = w;
}

void Objet::setHeight(int h)
{
    positionPlateau.h = h;
}

Objet::~Objet()
{
    //dtor
}
