#ifndef Voiture_joueur_hpp
#define Voiture_joueur_hpp

#include <stdio.h>
#include "Voiture.hpp"

class Voiture_joueur : public Voiture
{
public:
    Voiture_joueur();
    Voiture_joueur(int voitureType);
    
    void deplacer(SDL_Rect* route);
    void gestionTouches( SDL_Event& e );
    
    bool collision;

protected:
private:
    int X_VEL;
    bool deplacementGauche;
    bool deplacementDroit;
    bool accelerer;
    bool freiner;
};

#endif /* Voiture_joueur_hpp */
