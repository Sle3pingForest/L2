#include "Camera.hpp"

Camera::Camera()
{

}

Camera::~Camera()
{

}

void Camera::CameraInit( int vue, Route* route, Objet* plateau)
{
    if( vue == 0)
    {
        afficherTouteRoute(route);
    }
    else if (vue == 1)
    {
        afficherToutPlateau(route);
    }
    else
    {
        afficherToutPlateau(route);
    }
}

void Camera::gestionTouches( SDL_Event& event, Route* route, Objet* plateau )
{

    if( event.type == SDL_KEYDOWN )
    {
        switch( event.key.keysym.sym )
        {
        // Déplacement de la caméra
        case 'q':
            camera.x -= 100;
            break;

        case 'd':
            camera.x += 100;
            break;

        case 'z':
            camera.y -= 100;
            break;

        case 's':
            camera.y += 100;
            break;

        case 'a' :
            camera.w += 50;
            camera.h += 50;
            break;

        case 'e':
            camera.w -= 50;
            camera.h -= 50;
            break;

        case 'r':
            afficherRouteEchelle1(route);
            break;

        case 't' :
            afficherToutPlateau(plateau);
            break;

        case 'y' :
            afficherTouteRoute(route);
            break;

        default:
            break;
        }
    }
    calculerEchelle();
}

//Afficher la route centrée à l'echelle 1
void Camera::afficherRouteEchelle1(Route* route)
{
    camera.w = SCREEN_WIDTH;
    camera.h = SCREEN_HEIGHT;
    calculerEchelle();
    camera.x = (route->getPosX() * echelle) - ((SCREEN_WIDTH - route->calculerLargeurDansFenetre())/2); // Fonction
    camera.y = LEVEL_HEIGHT - SCREEN_HEIGHT;
}

// Afficher tout le plateau
void Camera::afficherToutPlateau(Objet* plateau)
{
    camera.w = LEVEL_WIDTH;
    camera.h = LEVEL_HEIGHT;
    calculerEchelle();
    camera.x = 0;
    camera.y = (plateau->calculerHauteurDansFenetre() - SCREEN_HEIGHT)/2;
}

//Afficher toute la hauteur de la route
void Camera::afficherTouteRoute(Route* route)
{
    camera.h = LEVEL_HEIGHT;
    camera.w = LEVEL_HEIGHT * ((float)SCREEN_WIDTH/(float)SCREEN_HEIGHT);
    calculerEchelle();
    camera.x = (route->getPosX() * echelle) - ((SCREEN_WIDTH - route->calculerLargeurDansFenetre())/2);
    camera.y = 0;
}

void Camera::calculerEchelle()
{
    echelle = (float)SCREEN_WIDTH / (float)camera.w;
}
