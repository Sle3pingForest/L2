#ifndef OBJET_H
#define OBJET_H

#include "SDL_Tools.hpp"

class Objet
{
public:
    Objet();
    Objet(int w, int h);
    Objet(int x, int y, int w, int h);
    virtual ~Objet();
    
    void placer(int x, int y);
    void deplacer(int x, int y);
    void afficher(SDL_Texture* texture);
    void afficherRectObjet();
    void calculerLargeur();
    void calculerHauteur();
    
    SDL_Rect calculerPosFenetre();
    int calculerLargeurDansFenetre();
    int calculerHauteurDansFenetre();
    
    
    int getPosX();
    int getPosY();
    int getWidth();
    int getHeight();
    SDL_Rect* getObjet();
    
    void setPosX(int x);
    void setPosY(int y);
    void setWidth(int w);
    void setHeight(int h);
    
protected:
    SDL_Rect positionPlateau;
    SDL_Rect image;
private:
};

#endif // OBJET_H
