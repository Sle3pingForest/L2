#ifndef PARTIE_H
#define PARTIE_H

#include "Decor_gestionnaire.hpp"
#include "Voiture_gestionnaire.hpp"
#include "Voiture_joueur.hpp"
#include "Route.hpp"
#include "Timer.hpp"

class Partie
{
public:
    Partie();
    virtual ~Partie();
    bool continuer_partie();
    void play();
    int FPS = 0;
protected:
private:
    bool jouer;
    bool pause;
    SDL_Texture* decorTexture;
    SDL_Texture* carsTexture;
    SDL_Texture* routeTexture;
    SDL_Texture* pauseTexture;
    Route route;
    Timer timerFPS;
    Timer timerDeplacement;
    Objet plateau;
    Decor_gestionnaire decor_gestionnaire;
    Voiture_gestionnaire voiture_gestionnaire;
    Voiture_joueur Test;
    
    void gestion_touches();
    void placer_Decors();
    void afficher();
    void deplacements();
    void calculerEchelle();
};

#endif // PARTIE_H
