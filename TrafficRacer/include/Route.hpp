#ifndef ROUTE_H
#define ROUTE_H
#include "Header.hpp"


class Route
{
    public:
        Route();
        Route(int weight, int height);
        int getWeightRoad();
        int getHeightRoad();
        int getColorRoad();
        SDL_Rect* getRectRoute();
        void AfficherRoute();
        virtual ~Route();
    protected:
    private:
        int weight;
        int height;
        SDL_Rect road;
};

#endif




