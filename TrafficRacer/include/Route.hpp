#ifndef ROUTE_H
#define ROUTE_H
#include "Header.hpp"


class Route
{
    public:
        Route();
        int getWeightRoad();
        int getHeightRoad();
        int getColorRoad();
        int getLargeurVoie();
        void tracerVoies(int nombre);
        SDL_Rect* getRectRoute();
        void AfficherRoute();
        virtual ~Route();
    protected:
    private:
        SDL_Rect road;
        SDL_Rect ligne;
        SDL_Rect ligne2;
        SDL_Rect ligne3;
};

#endif




