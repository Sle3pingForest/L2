#ifndef Objet_hpp
#define Objet_hpp

#include "Constantes.hpp"

class Objet
{
public:
    Objet();
    Objet(int w, int h);
    Objet(int x, int y, int w, int h);

    void placer(int x, int y);
    void deplacer(int x, int y);
    void afficher(SDL_Texture* texture);
    void afficherRectObjet();
    void calculerLargeur();
    void calculerHauteur();

    SDL_Rect calculerPosFenetre(SDL_Rect* RectACalculer);
    int calculerLargeurDansFenetre();
    int calculerHauteurDansFenetre();


    int getPosX();
    int getPosY();
    int getWidth();
    int getHeight();
    SDL_Rect* getObjet();
    SDL_Rect getObjetNormal();

    void setPosX(int x);
    void setPosY(int y);
    void setWidth(int w);
    void setHeight(int h);

protected:
    SDL_Rect positionPlateau;
    SDL_Rect image;
private:
};

#endif /* Objet_hpp */
