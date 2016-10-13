#ifndef VOITURE_H
#define VOITURE_H

#include "SDL_Tools.hpp"

class Voiture
{
    public:
        Voiture();
        Voiture(int w, int h);
        void placer( int x, int y);
        void AfficherVoiture();
        SDL_Rect* getRectCar();
        void setRectCar(SDL_Rect* car);
        int getPosX();
        int getPosY();
        int getCarWidth();
        int getCarHeight();
        int getCouleur();
        void setCouleur( int codeCouleur);
        void setWeight(int tailleW);
        void setHeight(int tailleH);
        void deplacer(int x, int y);
        virtual ~Voiture();
    protected:
    private:
        SDL_Rect rectCar;
        int couleur;
};

#endif // VOITURE_H

