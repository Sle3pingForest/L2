#ifndef Partie_hpp
#define Partie_hpp

#include "Constantes.hpp"
#include "Timer.hpp"
#include "Camera.hpp"
#include "Route.hpp"
#include "Decor_gestionnaire.hpp"
#include "Voiture_gestionnaire.hpp"
#include "Voiture_joueur.hpp"
<<<<<<< HEAD
=======
#include "Route.hpp"
#include "Timer.hpp"
#include "Camera.hpp"
#include "Joueur.hpp"

>>>>>>> c5892eaf1bdbc6875d694b1b708f13f732d54f52

class Partie
{
public:
    Partie();
<<<<<<< HEAD
    void play();
=======
    ~Partie();
    int play();

>>>>>>> c5892eaf1bdbc6875d694b1b708f13f732d54f52
protected:
private:
    bool jouer;
    bool pause;

    int FPS;
    int distance_parcourue;

    SDL_Texture* decorTexture;
    SDL_Texture* carsTexture;
    SDL_Texture* routeTexture;
    SDL_Texture* pauseTexture;

    Joueur player;
    Objet plateau;
    Camera camera;
    Route route;
    Decor_gestionnaire decor_gestionnaire;
    Voiture_gestionnaire voiture_gestionnaire;
    Voiture_joueur voitureJoueur;

    Timer timerFPS;
    Timer timerAfficherFPS;
    Timer timerDeplacement;

    void gestion_touches();
    void afficher();
<<<<<<< HEAD
    void deplacements();
    
    SDL_Texture* LoadBmpWithTransparency(const char* emplacement, Uint8 redTransparency, Uint8 greenTransparency, Uint8 blueTransparency);

=======
    int deplacements();
>>>>>>> c5892eaf1bdbc6875d694b1b708f13f732d54f52
};

#endif /* Partie_hpp */
