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
    X_VEL = 0.6 * vitesse;
    Y_VEL = 1;

    //Touches pressées
    if( event.type == SDL_KEYDOWN && event.key.repeat == 0 )
    {
        switch( event.key.keysym.sym )
        {
            case SDLK_LEFT:
                mVelX -= X_VEL;
                break;

            case SDLK_RIGHT:
                mVelX += X_VEL;
                break;

            case SDLK_UP:
                mVelY += 1;
                break;

            case SDLK_DOWN:
                mVelY -= 1;
                break;
        }
    }

    //Touches relachées
    else if( event.type == SDL_KEYUP && event.key.repeat == 0)
    {
        switch( event.key.keysym.sym )
        {
            case SDLK_LEFT:
                mVelX += X_VEL;
                deplacementGauche = false;
                break;

            case SDLK_RIGHT:
                mVelX -= X_VEL;
                deplacementDroit = false;
                break;

            case SDLK_UP:
                mVelY -= 1;
                break;

            case SDLK_DOWN:
                mVelY += 1;
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

    // Si collision on déplace pas
    if (collision)
    {
        positionPlateau.x  -= mVelX;
        collision = false;
    }

    vitesse += mVelY;
    // On limite la vitesse [0,25]
    if (vitesse > 25)
    {
        vitesse = 25;
    }
    else if (vitesse < 1)
    {
        vitesse = 1;
    }
    printf("V:%d X:%d Y:%d\n", vitesse, mVelX, mVelY);
}

void Voiture_joueur::eventCollision()
{
    positionPlateau.x -= mVelX;
    mVelX = 0;
    vitesse = 0;
}
