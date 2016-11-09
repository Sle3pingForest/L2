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
    
    void deplacer();
    void gestionTouches( SDL_Event& e );
    
    int Y_VEL = 10;
    static const int Vitesse_VEL = 2;
    
    int vitesse;

protected:
private:
    
    //The velocity of the dot
    int mVelX, mVelY;
    
};

#endif
