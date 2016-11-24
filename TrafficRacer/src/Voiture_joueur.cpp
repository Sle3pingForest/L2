#include "Voiture_joueur.hpp"

Voiture_joueur::Voiture_joueur() : Voiture()
{
    X_VEL = 0;
    collision = false;
    deplacementGauche = false;
    deplacementDroit = false;
    accelerer = false;
    freiner = false;
}

Voiture_joueur::Voiture_joueur(int voitureType) : Voiture_joueur()
{
    selectVoiture(voitureType);
}

void Voiture_joueur::gestionTouches( SDL_Event& event )
{
    //Touches pressées
    if( event.type == SDL_KEYDOWN && event.key.repeat == 0 )
    {
        switch( event.key.keysym.sym )
        {
            case SDLK_LEFT:
                deplacementGauche = true;
                break;

            case SDLK_RIGHT:
                deplacementDroit = true;
                break;

            case SDLK_UP:
                accelerer = true;
                break;

            case SDLK_DOWN:
                freiner = true;
                break;
        }
    }

    //Touches relachées
    else if( event.type == SDL_KEYUP && event.key.repeat == 0)
    {
        switch( event.key.keysym.sym )
        {
            case SDLK_LEFT:
                deplacementGauche = false;
                break;

            case SDLK_RIGHT:
                deplacementDroit = false;
                break;

            case SDLK_UP:
                accelerer = false;
                break;
                
            case SDLK_DOWN:
                freiner = false;
                break;
        }
    }
}

void Voiture_joueur::deplacer(SDL_Rect* route)
{
    X_VEL = 0.125 * vitesse;
    
    //Déplace la voiture
    if (deplacementGauche && !collision) {
        positionPlateau.x  -= X_VEL;
    }
    if (deplacementDroit && !collision) {
        positionPlateau.x  += X_VEL;
    }

    //Si elle est en dehors de la route à gauche
    if( ( positionPlateau.x < route->x ) )
    {
        //On ne déplace pas et on met tout à gauche dans la route
        positionPlateau.x  -= X_VEL;
        positionPlateau.x = route->x;
    }
    else if ( (positionPlateau.x + positionPlateau.w) > (route->x + route->w) )
    {
        //On ne déplace pas et on met tout à droite dans la route
        positionPlateau.x  -= X_VEL;
        positionPlateau.x = route->x + route->w - positionPlateau.w;
    }
    
    //Gestion de la vitesse
    if (accelerer) {
        ++vitesse;
    }
    if (freiner) {
        vitesse -= 2;
    }
    
    // On limite la vitesse [0,100]
    if (vitesse > 100)
    {
        vitesse = 100;
    }
    else if (vitesse < 1)
    {
        vitesse = 1;
    }
    
    if (collision) {
        vitesse = 10;
        collision = false;
    }
    printf("%d\n",vitesse);
}
