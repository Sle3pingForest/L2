#ifndef PARTIE_H
#define PARTIE_H

#include "Voiture.h"

class Partie
{
    public:
        Partie();
        virtual ~Partie();
        void gestion_evenements();
        void afficher();
        bool continuer_partie();
    protected:
    private:
        bool jouer;
        Voiture voiture_joueur;
        Voiture tabVoiture[10];
};

#endif // PARTIE_H
