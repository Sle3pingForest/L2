#ifndef DECOR_H
#define DECOR_H

#include "SDL_Tools.hpp"

class Decor
{
    public:
        Decor();
        Decor(int w ,int h, int x , int y);
        virtual ~Decor();
    
        void selectDecor(int type, int nb);
    
        void placer(int x, int y);
        void deplacer(int x, int y);
        void afficher(SDL_Texture* texture);
    
        int getPosX();
        int getPosY();
        int getDecorWidth();
        int getDecorHeight();
    
    protected:
    private:
        SDL_Rect rectDecor;
        SDL_Rect rectImage;
};

const int arbre_width = 64;
const int arbre_heigth = 118;

const int arbre_ligne = 0;
const int arbre_colone_1 = 0;
const int arbre_colone_2 = 65;
const int arbre_colone_3 = 131;
#endif // DECOR_H
