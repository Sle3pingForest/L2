#ifndef PARTIE_H
#define PARTIE_H

#include "Voiture.hpp"
#include "Route.hpp"
#include "Decor.hpp"
#include "SDL_Init.hpp"

class Partie
{
    public:
        Partie();
        virtual ~Partie();
        void gestion_evenements();
        void afficher();
        bool continuer_partie();
    protected:
    private:
        bool jouer;
        SDL_Texture* decorTexture;
        Voiture voiture_joueur;
        Route route;
        Voiture tabVoiture[10];
        Decor tabDecor[10];
};

#endif // PARTIE_H
