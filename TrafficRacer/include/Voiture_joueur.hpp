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
    int Y_VEL_OLD;
    int vitesse;
    bool collision;
    bool deplacementGauche;
    bool deplacementDroit;

protected:
private:

    //The velocity of the dot
    int mVelX, mVelY;

};

#endif
