#ifndef VOITURE_H
#define VOITURE_H
#include <SDL2/SDL.h>


class Voiture
{
    public:
        Voiture();
        Voiture(int w, int h);
        void placer( int x, int y);
        void AfficherVoiture();
        SDL_Rect* getRectCar();
        void setRectCar(SDL_Rect* car);
        int getCouleur();
        void setCouleur( int codeCouleur);
        void deplacer( int mouvement);
        virtual ~Voiture();
    protected:
    private:
        SDL_Rect rectCar;
        int couleur;
};

#endif // VOITURE_H

