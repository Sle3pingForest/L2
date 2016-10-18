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
        void gestion_decor(bool init);
        void afficher();
        bool colission(Voiture v, Voiture v2);
        bool continuer_partie();
    protected:
    private:
        bool jouer;
        SDL_Texture* decorTexture;
        SDL_Texture* carsTexture;
        Voiture voiture_joueur;
        Route route;
        Voiture tabVoiture[10];
        Decor tabDecor[10];
        Timer timerFPS;
};

#endif // PARTIE_H
