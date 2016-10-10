#ifndef DECOR_H
#define DECOR_H

#include <SDL2/SDL.h>

class Decor
{
    public:
        Decor();
        Decor(int w ,int h, int x , int y);
        virtual ~Decor();
        void afficher(int w, int h, SDL_Texture*);
        void deplacer(int x, int y);
    protected:
    private:
        SDL_Rect rectDecor;
};

#endif // DECOR_H
