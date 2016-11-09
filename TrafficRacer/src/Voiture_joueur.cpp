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
        //Adjust the velocity
        switch( event.key.keysym.sym )
        {
            case SDLK_LEFT: mVelX -= Y_VEL; break;
            case SDLK_RIGHT: mVelX += Y_VEL; break;
        }
    }

    //Touches relachées
    else if( event.type == SDL_KEYUP && event.key.repeat == 0 )
    {
        //Adjust the velocity
        switch( event.key.keysym.sym )
        {
            case SDLK_LEFT: mVelX += Y_VEL; break;
            case SDLK_RIGHT: mVelX -= Y_VEL; break;
        }
    }

    // On limite la vitesse entre 0 et 20
    if( event.type == SDL_KEYDOWN )
    {
        switch( event.key.keysym.sym )
        {
            case SDLK_UP:
                vitesse += Vitesse_VEL;
                if( vitesse > 20)
                {
                    vitesse = 20;
                }
                break;
            case SDLK_DOWN:
                vitesse -= Vitesse_VEL+1;
                if( vitesse < 0)
                {
                    vitesse = 0;
                }
                break;
                break;
        }

    }
}

void Voiture_joueur::deplacer(SDL_Rect* route)
{
    //Déplace la voiture
    positionPlateau.x  += mVelX;

    //Si elle est trop loin (en dehors de la route)
    if( ( positionPlateau.x < route->x ) || ( (positionPlateau.x + positionPlateau.w) > (route->x + route->w) ))
    {
        //On ne déplace pas
        positionPlateau.x  -= mVelX;
    }
    //printf("%d\n", mVelX);
}

void Voiture_joueur::eventCollision()
{
    vitesse = 3;
    mVelX = 0;
}
