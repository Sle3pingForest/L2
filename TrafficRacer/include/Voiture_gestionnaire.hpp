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
    ~Voiture_gestionnaire();

    void afficherVoitures(SDL_Texture* carsTexture);
    void chargement(Route* route);
    bool gestion(int vitesse, SDL_Rect* rectVoitureJoueur);
    void klaxon(Route* route, SDL_Rect* rectVoitureJoueur);

private:
    static const int nb_voitures_max = 10;
    Voiture* tabVoitures[4][nb_voitures_max];
    int posVoitureTete;
    int niveau;
    std::ifstream fichier;

    void chargement_voitures_fichier(Route* route);
    void chargement_aleatoire(Route* route);
    bool isDead(int i, int j);
    void checkVoitTete(int i, int j);
    bool depassement(int i, int j);
    void testDepassement(int i, int j);

    bool peutDepasser(int i, int j);
    void changementVoieGauche(int i, int j);
    SDL_bool collisionVoitJoueur(int i, int j, SDL_Rect* rectVoitureJoueur);
};

#endif /* Voiture_gestionnaire_hpp */
