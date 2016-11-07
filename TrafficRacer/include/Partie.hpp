#ifndef PARTIE_H
#define PARTIE_H

#include "Voiture.hpp"
#include "Route.hpp"
#include "Decor.hpp"
#include "Timer.hpp"
#include <fstream>

class Partie
{
public:
    Partie();
    virtual ~Partie();
    void gestion_touches();
    void placer_Decors();
    void afficher();
    bool collision(Voiture v, Voiture v2);
    void chargement_voitures_fichier();
    void deplacements();
    void gestion_collisions();
    void gestion_decors();
    void gestion_voitures();
    void calculerEchelle();
    bool continuer_partie();
    int FPS = 0;
protected:
private:
    bool jouer;
    bool pause;
    int vitesse;
    SDL_Texture* decorTexture;
    SDL_Texture* carsTexture;
    SDL_Texture* routeTexture;
    SDL_Texture* pauseTexture;
    SDL_Texture* testTexture;
    Route route;
    Voiture voiture_joueur;
    Voiture* tabVoit[20];
    Voiture tabVoiture[10];
    Decor* tabDecors[30];
    Timer timerFPS;
    Timer timerDeplacement;
    Timer timerChargementFichier;
    Objet plateau;
};

#endif // PARTIE_H
