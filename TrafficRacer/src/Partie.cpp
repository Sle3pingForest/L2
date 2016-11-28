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

    timerFPS.start();
    timerAfficherFPS.start();
    timerDeplacement.start();

    srand((unsigned int)time(NULL));

    plateau.setWidth(LEVEL_WIDTH);
    plateau.setHeight(LEVEL_HEIGHT);

    camera.CameraInit(1, &route, &plateau);

    voitureJoueur.selectVoiture(0);
    voitureJoueur.setWidth(route.getLargeurVoiePlateau() - 15);
    voitureJoueur.calculerHauteur();
    voitureJoueur.placer(LEVEL_WIDTH/2, LEVEL_HEIGHT - voitureJoueur.getHeight() - 50);
    voitureJoueur.vitesse = 10;

    distance_parcourue = 0;
}

<<<<<<< HEAD
void Partie::play()
=======
Partie::~Partie()
{
    //dtor
    SDL_DestroyRenderer(pRenderer);
    SDL_DestroyWindow(pWindow);
    SDL_Quit();
}

int Partie::play()
>>>>>>> c5892eaf1bdbc6875d694b1b708f13f732d54f52
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
    //player.setScore(distance_parcourue/1000);
    return deplacements()/1000;
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

                case 'm' :
                    jouer = false;

                default:
                    break;
            }
        }
    }
}

int Partie::deplacements()
{
    if (not pause) {
        distance_parcourue = (voitureJoueur.vitesse * timerDeplacement.getTicks())/100;
        int vitesse = voitureJoueur.vitesse / (SCREEN_FPS * 0.0625); // Permet d'avoir un vitesse constante quelque soit les FPS
        
        route.deplacer(vitesse);

        decor_gestionnaire.gestion(vitesse);
        
        voiture_gestionnaire.chargement(&route, distance_parcourue);
        
        if ( voiture_gestionnaire.gestion(vitesse, voitureJoueur.getObjet())) {
            voitureJoueur.collision = true;
        }
        voitureJoueur.deplacer(route.getObjet());
    }
    return distance_parcourue;
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
    //SDL_SetRenderDrawColor(pRenderer, 0, 0, 255, 150);
    //route.afficherRectObjet();
    //SDL_SetRenderDrawColor(pRenderer, 0, 255, 0, 255);
    //route.afficherVoies();

    //Affichage des voitures
    voiture_gestionnaire.afficherVoitures(carsTexture);

    //Affichage voiture joueur
    //SDL_SetRenderDrawColor(pRenderer, 0, 255, 255, 255);
    //voitureJoueur.afficherRectObjet();
    voitureJoueur.afficher(carsTexture);
//    SDL_SetRenderDrawColor(pRenderer, 0, 0, 255, 120);
//    voitureJoueur.afficherRectCollision();

//    Decor testDecor;
//    testDecor.placer(200, 200);
//    testDecor.selectDecor(1, 3);
//    testDecor.afficher(decorTexture);
//
//    Objet testObjet;
//    testObjet.placer(1000, 500);
//    testObjet.setWidth(route.getWidth()/4);
//    testObjet.setHeight(250);
//    testObjet.afficherRectObjet();
//
//    Voiture testVoiture;
//    testVoiture.selectVoiture(0);
//    testVoiture.placer(200, 200);
//    testVoiture.setWidth(200);
//    testVoiture.setHeight(200);
//    testVoiture.selectVoiture(0);
//    testVoiture.afficherRectObjet();
//    testVoiture.afficher(carsTexture);

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

SDL_Texture* Partie::LoadBmpWithTransparency(const char* emplacement, Uint8 redTransparency, Uint8 greenTransparency, Uint8 blueTransparency)
{
    SDL_Surface *loadedImage = NULL;
    SDL_Texture *texture = NULL;
    
    loadedImage = SDL_LoadBMP(emplacement);
    
    if(loadedImage != NULL) {
        Uint32 colorkey = SDL_MapRGB( loadedImage->format, redTransparency, greenTransparency, blueTransparency);
        SDL_SetColorKey(loadedImage, SDL_TRUE, colorkey);
        texture = SDL_CreateTextureFromSurface(pRenderer, loadedImage);
        SDL_FreeSurface(loadedImage);
        return texture;
    }
    else {
        fprintf(stderr, "Échec du chargement de l'image: %s\n", SDL_GetError());
        return NULL;
    }
}
