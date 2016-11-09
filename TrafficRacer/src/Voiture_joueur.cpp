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

void Voiture_joueur::gestionTouches( SDL_Event& e )
{
    Y_VEL = 0.7 * vitesse;
    //If a key was pressed
    if( e.type == SDL_KEYDOWN && e.key.repeat == 0 )
    {
        //Adjust the velocity
        switch( e.key.keysym.sym )
        {
            case SDLK_UP: vitesse += Vitesse_VEL; break;
            case SDLK_DOWN: vitesse -= Vitesse_VEL; break;
            case SDLK_LEFT: mVelX -= Y_VEL; break;
            case SDLK_RIGHT: mVelX += Y_VEL; break;
        }
    }
    //If a key was released
    else if( e.type == SDL_KEYUP && e.key.repeat == 0 )
    {
        //Adjust the velocity
        switch( e.key.keysym.sym )
        {
//            case SDLK_UP: vitesse -= Vitesse_VEL; break;
//            case SDLK_DOWN: vitesse += Vitesse_VEL; break;
            case SDLK_LEFT: mVelX += Y_VEL; break;
            case SDLK_RIGHT: mVelX -= Y_VEL; break;
        }
    }
}

void Voiture_joueur::deplacer()
{
    //Move the dot left or right
    positionPlateau.x  += mVelX;
    
    //If the dot went too far to the left or right
    //if( ( mPosX < 0 ) || ( mPosX + DOT_WIDTH > SCREEN_WIDTH ) )
    {
        //Move back
        //mPosX -= mVelX;
    }
}
