#ifndef ROUTE_H
#define ROUTE_H

#include "Objet.hpp"

class Route : public Objet
{
    public:
        Route();
        Route(int w, int h, int x, int y);
        virtual ~Route();

        int getLargeurVoie();
        void afficher(SDL_Texture* texture);
        void afficherVoies();
        void deplacer(int vitesse);

    protected:
    private:
};

#endif




