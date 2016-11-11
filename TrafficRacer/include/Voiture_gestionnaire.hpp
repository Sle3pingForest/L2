#ifndef Voiture_gestionnaire_hpp
#define Voiture_gestionnaire_hpp

#include <stdio.h>
#include <fstream>
#include "Voiture.hpp"
#include "Timer.hpp"
#include "Route.hpp"

using namespace std;


class Voiture_gestionnaire {
public:
    Voiture_gestionnaire();
    virtual ~Voiture_gestionnaire();

    bool gestion_voitures(int vitesse, SDL_Rect* rectVoitureJoueur);
    void chargement_voitures_fichier(Route* route);
    void afficherVoitures(SDL_Texture* carsTexture);
    void depassement(Route route);

private:
    static const int nb_voiture_max = 10;
    int nb_voitures;
    Voiture* tabVoitures[nb_voiture_max];
    Timer timerChargementFichier;

};

#endif
