#include "Voiture.hpp"
#include "Route.hpp"

Voiture::Voiture()
{
    objet.w = 0;
    objet.h = 0;
    objet.x = 0;
    objet.y = 0;
    
    image.x = 0;
    image.y = 0;
    image.w = 0;
    image.h = 0;
}

Voiture::Voiture(int x, int y, int w, int h)
{
    positionPlateau.x = x;
    positionPlateau.y = y;
    positionPlateau.w = w;
    positionPlateau.h = h;
}

void Voiture::selectVoiture(int nb)
{
    switch (nb) {
        case 0:
            image.x = audi_x;
            image.y = audi_y;
            image.w = audi_w;
            image.h = audi_h;
            break;
            
        case 1:
            image.x = car_x;
            image.y = car_y;
            image.w = car_w;
            image.h = car_h;
            break;

        case 2:
            image.x = viper_x;
            image.y = viper_y;
            image.w = viper_w;
            image.h = viper_h;
            break;

        case 3:
            image.x = miniTruck_x;
            image.y = miniTruck_y;
            image.w = miniTruck_w;
            image.h = miniTruck_h;
            break;
            
        case 4:
            image.x = ambulance_x;
            image.y = ambulance_y;
            image.w = ambulance_w;
            image.h = ambulance_h;
            break;

        case 5:
            image.x = van_x;
            image.y = van_y;
            image.w = van_w;
            image.h = van_h;
            break;

        case 6:
            image.x = taxi_x;
            image.y = taxi_y;
            image.w = taxi_w;
            image.h = taxi_h;
            break;

        case 7:
            image.x = truck_x;
            image.y = truck_y;
            image.w = truck_w;
            image.h = truck_h;
            break;

        default:
            break;
    }
}


Voiture::~Voiture()
{
    //dtor
}
