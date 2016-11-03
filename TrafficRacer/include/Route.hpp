#ifndef ROUTE_H
#define ROUTE_H

#include "Objet.hpp"

class Route : public Objet
{
public:
    Route();
    Route(int w, int h, int x, int y);
    virtual ~Route();

    int getLargeurVoiePlateau();
    int getLargeurVoieFenetre();
    void afficherDefilement(SDL_Texture* texture);
    void afficherVoies();

    void deplacer(int vitesse);

protected:
private:
    int position_y;
};

#endif




