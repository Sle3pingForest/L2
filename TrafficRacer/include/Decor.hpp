#ifndef DECOR_H
#define DECOR_H

#include "Objet.hpp"

class Decor: public Objet
{
public:
    Decor();
    Decor(int x, int y, int type, int typeNb);
    virtual ~Decor();
    
    void selectDecor(int type, int nb);
    bool isDead();
    
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
