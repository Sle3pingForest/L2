#ifndef DECOR_H
#define DECOR_H

#include "SDL_Tools.hpp"
#include "Objet.hpp"

class Decor: public Objet
{
    public:
        Decor();
        Decor(int w ,int h, int x , int y);
        virtual ~Decor();

        void selectDecor(int type, int nb);

    protected:
    private:
};

const int arbre_width = 64;
const int arbre_heigth = 118;

const int arbre_ligne = 0;
const int arbre_colone_1 = 0;
const int arbre_colone_2 = 65;
const int arbre_colone_3 = 131;
#endif // DECOR_H
