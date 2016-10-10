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
        void InitVoie();
        void setVoie(int x);
        void tracerVoies(int nombre);
        SDL_Rect* getRectRoute();
        void AfficherRoute();
        virtual ~Route();
    protected:
    private:
        SDL_Rect road;
        SDL_Rect tabVoie[4];
};

#endif




