#include "Voiture_joueur.hpp"

Voiture_joueur::Voiture_joueur() : Voiture()
{

}

Voiture_joueur::Voiture_joueur(int voitureType)
{
    selectVoiture(voitureType);
}

Voiture_joueur::~Voiture_joueur()
{

}

void Voiture_joueur::gestionTouches( SDL_Event& event )
{
    Y_VEL = 0.7 * vitesse;

    //Touches pressées
    if( event.type == SDL_KEYDOWN && event.key.repeat == 0 )
    {
        switch( event.key.keysym.sym )
        {
            case SDLK_LEFT: mVelX -= Y_VEL; break;
            case SDLK_RIGHT: mVelX += Y_VEL; break;
        }
    }

    //Touches relachées
    else if( event.type == SDL_KEYUP && event.key.repeat == 0 )
    {
        switch( event.key.keysym.sym )
        {
            case SDLK_LEFT: mVelX = 0; break;
            case SDLK_RIGHT: mVelX = 0; break;
        }
    }

    // On limite la vitesse entre 0 et 20
    if( event.type == SDL_KEYDOWN )
    {
        switch( event.key.keysym.sym )
        {
            case SDLK_UP:
                vitesse += 1;
                if( vitesse > 20)
                {
                    vitesse = 20;
                }
                break;
            case SDLK_DOWN:
                vitesse -= 3;
                if( vitesse < 0)
                {
                    vitesse = 0;
                }
                break;
        }
    }
}

void Voiture_joueur::deplacer(SDL_Rect* route)
{
    //Déplace la voiture
    positionPlateau.x  += mVelX;

    //Si elle est en dehors de la route à gauche
    if( ( positionPlateau.x < route->x ) )
    {
        //On ne déplace pas et on met tout à gauche dans la route
        positionPlateau.x  -= mVelX;
        positionPlateau.x = route->x;
    }
    else if ( (positionPlateau.x + positionPlateau.w) > (route->x + route->w) )
    {
        //On ne déplace pas et on met tout à droite dans la route
        positionPlateau.x  -= mVelX;
        positionPlateau.x = route->x + route->w - positionPlateau.w;
    }
}

void Voiture_joueur::eventCollision()
{
    vitesse = 3;
}
