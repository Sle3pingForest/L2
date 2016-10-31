#include "Objet.hpp"

Objet::Objet() // constructeur sans parametre
{
    objet.x = 0;
    objet.y = 0;
    objet.w = 0;
    objet.h = 0;

    image.x = 0;
    image.y = 0;
    image.w = 0;
    image.h = 0;
}

Objet::Objet( int w, int h)
{
    objet.w = w;
    objet.h = h;
}

Objet::Objet( int x, int y, int w, int h)
{
    objet.x = x;
    objet.y = y;
    objet.w = w;
    objet.h = h;
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
    SDL_Rect positionFenetre = calculerPosFenetre();
    SDL_RenderCopy(pRenderer, texture, &image, &positionFenetre);
}

void Objet::afficherRectObjet()
{
    SDL_Rect positionFenetre = calculerPosFenetre();
    SDL_RenderFillRect(pRenderer, &positionFenetre);
}

void Objet::calculerLargeur()
{
    objet.w = image.w * objet.h / image.h;
}

void Objet::calculerHauteur()
{
    positionPlateau.h = image.h * positionPlateau.w / image.w;
}

SDL_Rect Objet::calculerPosFenetre()
{
    SDL_Rect positionFenetre;
    //Calcul du déplacement
    positionFenetre.x = (positionPlateau.x * echelle) - camera.x;
    positionFenetre.y = (positionPlateau.y * echelle) - camera.y;
    //Calcul du redimensionnement
    positionFenetre.w = positionPlateau.w * echelle;
    positionFenetre.h = positionPlateau.h * echelle;
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
