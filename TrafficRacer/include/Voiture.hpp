#ifndef VOITURE_H
#define VOITURE_H

#include "SDL_Tools.hpp"
#include "Objet.hpp"

class Voiture : public Objet
{
    public:
        Voiture();
        Voiture(int x, int y, int w, int h);
        virtual ~Voiture();

    protected:
    private:
};

#endif // VOITURE_H

