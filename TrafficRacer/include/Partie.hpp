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
        bool continuer_partie();
        int FPS = 0;
    protected:
    private:
        bool jouer;
        SDL_Texture* decorTexture;
        SDL_Texture* carsTexture;
        SDL_Texture* roadTexture;
        Voiture voiture_joueur;
        Route route;
        Voiture tabVoiture[10];
        Decor tabDecor[10];
        Timer timerFPS;
        Timer timerDeplacement;
        int vitesse;
        bool pause = false;
    
};

#endif // PARTIE_H
