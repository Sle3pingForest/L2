#include "Voiture.hpp"
#include "Route.hpp"

Voiture::Voiture()
{
    positionPlateau.w = 0;
    positionPlateau.h = 0;
    positionPlateau.x = 0;
    positionPlateau.y = 0;

    image.x = 0;
    image.y = 0;
    image.w = 0;
    image.h = 0;

    rectCollision.x = 0;
    rectCollision.y = 0;
    rectCollision.w = 0;
    rectCollision.h = 0;
}

Voiture::Voiture(int posX, int posY, int widht, int voitureType)
{
    positionPlateau.x = posX;
    positionPlateau.y = posY;

    selectVoiture(voitureType);
    positionPlateau.w = widht;
    calculerHauteur();
    calculerRectCollision();
}

void Voiture::selectVoiture(int nb)
{
    switch (nb) {
        case 0:
            image = audi;
            break;

        case 1:
            image = car;
            break;

        case 2:
            image = viper;
            break;

        case 3:
            image = miniTruck;
            break;

        case 4:
            image = ambulance;
            break;

        case 5:
            image = van;
            break;

        case 6:
            image = taxi;
            break;

        case 7:
            image = truck;
            break;

        default:
            break;
    }
}

bool Voiture::isDead()
{
    if (positionPlateau.y > LEVEL_HEIGHT + 2000)
        return true;
    return false;
}

void Voiture::afficherRectCollision()
{
    calculerRectCollision();
    SDL_Rect positionFenetre = calculerPosFenetre(&rectCollision);
    SDL_SetRenderDrawColor(pRenderer, 255, 255, 0, 120);
    SDL_RenderFillRect(pRenderer, &positionFenetre);
}

void Voiture::calculerRectCollision()
{
    // On réduit la taille de l'objet dans le rect de collision pour améliorer les collisions
    rectCollision = positionPlateau;
    rectCollision.x += (rectCollision.w * 0.2) / 2;
    rectCollision.w -= rectCollision.w * 0.2;
}

int Voiture::getVitesseVoiture()
{
    return vitesse;
}


void Voiture::setVitesseVoiture( int newVitesse)
{
    vitesse = newVitesse;
}

void Voiture::avancer(int vitesseJeu)
{
    positionPlateau.y += vitesseJeu - (vitesse);
}

SDL_Rect* Voiture::getRectCollision()
{
    calculerRectCollision();
    return &rectCollision;
}
