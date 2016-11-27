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

    bool gestion_voitures(int vitesse, SDL_Rect* rectVoitureJoueur);
    void afficherVoitures(SDL_Texture* carsTexture);
    void depassement(Route *route);
    void MegaFonction(int vitesse, SDL_Rect* rectVoitureJoueur);
    void chargement(Route* route, int distance_parcourue);

private:
    static const int nb_voitures_max = 10;
    Voiture* tabVoitures[4][nb_voitures_max];

    int posVoitureTete;
    
    int niveau;
    void chargement_voitures_fichier(Route* route, int distance_parcourue);
    void chargement_aleatoire(Route* route, int distance_parcourue);


    std::ifstream fichier;
    bool isDead(int i, int j);
    void checkVoitTete(int i, int j);
    bool depassementNEW(int i, int j);
    void changementVoieGauche(int i, int j);
    SDL_bool collisionVoitJoueur(int i, int j, SDL_Rect* rectVoitureJoueur);

};

#endif /* Voiture_gestionnaire_hpp */
