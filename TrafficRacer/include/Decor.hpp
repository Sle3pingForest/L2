#ifndef DECOR_H
#define DECOR_H
#include <SDL2/SDL.h>

class Decor
{
    public:
        Decor();
        Decor(int w ,int h, int x , int y);
        virtual ~Decor();
        void placer(int x, int y);
        void CreateDecor();
        SDL_Rect* getRectDecor();
        void setRectDecor(SDL_Rect* decor);
    protected:
    private:
        SDL_Rect rectDecor;
};

#endif // DECOR_H
