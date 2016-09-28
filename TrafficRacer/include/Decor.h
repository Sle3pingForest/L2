#ifndef DECOR_H
#define DECOR_H

#include <SDL2/SDL.h>

class Decor
{
    public:
        Decor();
        virtual ~Decor();
        void placer(int x, int y);
        SDL_Rect rectDecor;
    protected:
    private:

};

#endif // DECOR_H
