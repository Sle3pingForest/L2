#ifndef OBJET_H
#define OBJET_H

#include "SDL_Tools.hpp"

class Objet
{
    public:
        Objet();
        Objet(int w, int h);
        Objet(int w, int h, int x, int y);

        void placer(int x, int y);
        void afficher(SDL_Texture* texture);
        void afficherObjet();
        void deplacer(int x, int y);

        int getPosX();
        int getPosY();
        int getWidth();
        int getHeight();
        void setPosX(int x);
        void setPosY(int y);
        void setWidth(int w);
        void setHeight(int h);
        SDL_Rect* getObjet();
        virtual ~Objet();

    protected:
        SDL_Rect objet;
        SDL_Rect image;
    private:
};

#endif // OBJET_H
