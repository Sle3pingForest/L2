#ifndef VOITURE_H
#define VOITURE_H

#include "Objet.hpp"

class Voiture : public Objet
{
public:
    Voiture();
    Voiture(int posX, int posY, int widht, int voitureType);
    virtual ~Voiture();
    void avancer(int vitesseJeu);
    void selectVoiture(int nb);
    bool isDead();
    void afficherRectCollision();
    void calculerRectCollision();
    int getVitesseVoiture();
    int getVoie();
    void setVoie(int numero);
    void setVitesseVoiture( int newVitesse);
    SDL_Rect* getRectCollision();
protected:
private:
    SDL_Rect rectCollision;
    int vitesse;
    int numeroVoie;
};

const int audi_x = 0;
const int audi_y = 0;
const int audi_w = 98;
const int audi_h = 214;

const int car_x = 98;
const int car_y = 0;
const int car_w = 92;
const int car_h = 216;

const int viper_x = 190;
const int viper_y = 0;
const int viper_w = 103;
const int viper_h = 216;

const int miniTruck_x = 0;
const int miniTruck_y = 230;
const int miniTruck_w = 111;
const int miniTruck_h = 204;

const int ambulance_x = 111;
const int ambulance_y = 230;
const int ambulance_w = 101;
const int ambulance_h = 207;

const int van_x = 212;
const int van_y = 230;
const int van_w = 93;
const int van_h = 196;

const int taxi_x = 0;
const int taxi_y = 438;
const int taxi_w = 114;
const int taxi_h = 223;

const int truck_x = 305;
const int truck_y = 0;
const int truck_w = 193;
const int truck_h = 616;

#endif // VOITURE_H

