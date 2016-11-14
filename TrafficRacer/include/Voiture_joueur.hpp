#ifndef Voiture_joueur_hpp
#define Voiture_joueur_hpp

#include <stdio.h>
#include "Voiture.hpp"

class Voiture_joueur : public Voiture
{
public:
    Voiture_joueur();
    Voiture_joueur(int voitureType);
    virtual ~Voiture_joueur();

    void deplacer(SDL_Rect* route);
    void gestionTouches( SDL_Event& e );
    void eventCollision();

    int Y_VEL;
    static const int Vitesse_VEL = 1;

    int vitesse;

protected:
private:

    //The velocity of the dot
    int mVelX, mVelY;

};

#endif /* Voiture_joueur_hpp */
