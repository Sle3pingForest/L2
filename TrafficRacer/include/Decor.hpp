#ifndef DECOR_H
#define DECOR_H

#include <SDL2/SDL.h>
#include "Route.hpp"
#include "SDL_Init.hpp"

class Decor
{
    public:
        Decor();
        Decor(int w ,int h, int x , int y);
        virtual ~Decor();
        void afficher(SDL_Texture*);
        void placer(int x, int y);
        void deplacer(int x, int y);
        int getPosX();
        int getPosY();
        int getDecorWidth();
        int getDecorHeight();
    protected:
    private:
        SDL_Rect rectDecor;
};

#endif // DECOR_H
