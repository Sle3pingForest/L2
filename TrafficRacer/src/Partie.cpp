#include "Partie.hpp"

const int LEVEL_WIDTH = 2000;
const int LEVEL_HEIGHT = 1200;

SDL_Rect camera;
float echelle;

Partie::Partie()
{
    jouer = true;
    pause = false;

    decorTexture = LoadBmpWithTransparency("autres/images/decor.bmp", 0, 255, 255);
    carsTexture = LoadBmpWithTransparency("autres/images/cars.bmp", 0, 255, 255);
    routeTexture = LoadBmpWithTransparency("autres/images/road.bmp", 0, 255, 255);
    pauseTexture = LoadBmpWithTransparency("autres/images/pause.bmp", 0, 255, 255);

    timerAfficherFPS.start();
    timerDeplacement.start();

    srand((unsigned int)time(NULL));

    plateau.setWidth(LEVEL_WIDTH);
    plateau.setHeight(LEVEL_HEIGHT);

    camera.CameraInit(0, &route, &plateau);

    voitureJoueur.selectVoiture(0);
    voitureJoueur.setWidth(route.getLargeurVoiePlateau() - 15);
    voitureJoueur.calculerHauteur();
    voitureJoueur.placer(LEVEL_WIDTH/2, LEVEL_HEIGHT - voitureJoueur.getHeight() - 50);
    voitureJoueur.setVitesseVoiture(10);

    distance_parcourue = 0;
}

int Partie::play()
{
    while (jouer) {
        Uint32 startTicks = SDL_GetTicks();
        gestion_touches();
        deplacements();
        afficher();
        if(timerAfficherFPS.getTicks() >= 1000) {
            //printf("FPS : %d\n", FPS);
            FPS = 0;
            timerAfficherFPS.start();
        }
        int reste = 1000/SCREEN_FPS - (SDL_GetTicks() - startTicks);
        if (reste > 0) {
            SDL_Delay(reste);
        }
    }
    return distance_parcourue/1000;
}

void Partie::gestion_touches()
{
    SDL_Event event;
    while( SDL_PollEvent( &event ) != 0 ) {
        //Fermer la fenêtre
        if(event.type == SDL_QUIT) {
            jouer = false;
        }

        //Evenements de fenêtre
        if(event.type == SDL_WINDOWEVENT) {
            switch (event.window.event) {
            case SDL_WINDOWEVENT_SIZE_CHANGED:
                SCREEN_WIDTH = event.window.data1;
                SCREEN_HEIGHT = event.window.data2;
                camera.afficherTouteRoute(&route);
                break;

            case SDL_WINDOWEVENT_FOCUS_LOST:
                if(not pause)
                    //pause = true;
                break;
            }

        }

        // Les touches de déplacement de la voiture
        voitureJoueur.gestionTouches( event );

        // Les touches de la caméra
        camera.gestionTouches(event, &route, &plateau);

        // Les autres touches
        if( event.type == SDL_KEYDOWN && event.key.repeat == 0 ) {
            switch( event.key.keysym.sym ) {
                case 'p':
                    if(pause)
                        pause = false;
                    else
                        pause = true;
                    break;

                case SDLK_ESCAPE :
                    jouer = false;
                    
                case SDLK_SPACE:
                    voiture_gestionnaire.klaxon(&route, voitureJoueur.getObjet());
                    break;
                    
                default:
                    break;
            }
        }
    }
}

void Partie::deplacements()
{
    if (not pause) {
        distance_parcourue = (voitureJoueur.getVitesseVoiture() * timerDeplacement.getTicks())/100;
        int vitesse = voitureJoueur.getVitesseVoiture() / (SCREEN_FPS * 0.0625); // Permet d'avoir un vitesse constante quelque soit les FPS

        route.deplacer(vitesse);

        decor_gestionnaire.gestion(vitesse);

        voiture_gestionnaire.chargement(&route);

        if ( voiture_gestionnaire.gestion(vitesse, voitureJoueur.getObjet())) {
            voitureJoueur.collision = true;
        }
        voitureJoueur.deplacer(route.getObjet());
    }
}

void Partie::afficher()
{
    //Création de la couleur de fond
    SDL_SetRenderDrawColor(pRenderer, 40, 40, 40, 255);
    SDL_RenderClear(pRenderer);

    //Affichage le plateau
    SDL_SetRenderDrawColor(pRenderer, 88, 41, 0, 255);
    plateau.afficherRectObjet();

    //Affichages des décors
    decor_gestionnaire.afficherDecors(decorTexture);

    //Affichage de la route
    route.afficherDefilement(routeTexture);

    //Affichage des voitures
    voiture_gestionnaire.afficherVoitures(carsTexture);

    //Affichage voiture joueur
    voitureJoueur.afficher(carsTexture);

    if (pause) {
        SDL_Rect pause;
        pause.w = SCREEN_WIDTH*0.5;
        pause.h = pause.w;
        pause.x = (SCREEN_WIDTH - pause.w) / 2;
        pause.y = (SCREEN_HEIGHT - pause.h) / 2;
        SDL_SetTextureAlphaMod(pauseTexture, 200);
        SDL_RenderCopy(pRenderer, pauseTexture, NULL, &pause);
    }

    SDL_RenderPresent(pRenderer);

    FPS++;
}
