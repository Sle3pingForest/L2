#ifndef Voiture_hpp
#define Voiture_hpp

#include "Objet.hpp"
#include "Route.hpp"

class Voiture : public Objet
{
public:
    Voiture();
    Voiture(int posX, int posY, int widht, int voitureType);

    void avancer(int vitesseJeu);
    void selectVoiture(int nb);
    bool isDead();
    void afficherRectCollision();
    void calculerRectCollision();
    int getVitesseVoiture();
    void setVitesseVoiture( int newVitesse);
    SDL_Rect* getRectCollision();
    int vitesse;
protected:
private:
    SDL_Rect rectCollision;
};

const SDL_Rect audi =       {0, 0, 98, 214};
const SDL_Rect car =        {98, 0, 92, 216};
const SDL_Rect viper =      {190, 0, 103, 216};
const SDL_Rect miniTruck =  {0, 230, 101, 207};
const SDL_Rect ambulance =  {111, 230, 101, 207};
const SDL_Rect van =        {212, 230, 93, 196};
const SDL_Rect taxi =       {0, 438, 114, 223};
const SDL_Rect truck =      {305, 0, 193, 616};

#endif /* Voiture_hpp */
