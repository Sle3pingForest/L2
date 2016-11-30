#ifndef Partie_hpp
#define Partie_hpp

#include "Constantes.hpp"
#include "SDL_Tools.hpp"
#include "Timer.hpp"
#include "Camera.hpp"
#include "Route.hpp"
#include "Decor_gestionnaire.hpp"
#include "Voiture_gestionnaire.hpp"
#include "Voiture_joueur.hpp"

class Partie
{
public:
    Partie();
    int play();

protected:
private:
    bool jouer;
    bool pause;

    int FPS;
    int distance_parcourue;

    SDL_Texture* decorTexture;
    SDL_Texture* carsTexture;
    SDL_Texture* routeTexture;
    SDL_Texture* pauseTexture;

    Objet plateau;
    Camera camera;
    Route route;
    Decor_gestionnaire decor_gestionnaire;
    Voiture_gestionnaire voiture_gestionnaire;
    Voiture_joueur voitureJoueur;

    Timer timerFPS;
    Timer timerAfficherFPS;
    Timer timerDeplacement;

    void gestion_touches();
    void afficher();
    void deplacements();
};

#endif /* Partie_hpp */
