#include "Partie.hpp"

SDL_Window *pWindow =NULL;
SDL_Renderer *pRenderer = NULL;

int SCREEN_WIDTH = 700;
int SCREEN_HEIGHT = 700;
int SCREEN_FPS = 50;

int LEVEL_WIDTH = 2000;
int LEVEL_HEIGHT = 1200;

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
    timerDeplacement.start();

    srand((unsigned int)time(NULL));

    plateau.setWidth(LEVEL_WIDTH);
    plateau.setHeight(LEVEL_HEIGHT);

    //Initialisation de la position de la caméra
    camera.w = LEVEL_WIDTH;
    camera.h = LEVEL_HEIGHT;
    calculerEchelle();
    camera.x = 0;
    camera.y = (plateau.calculerHauteurDansFenetre() - SCREEN_HEIGHT)/2;

    Test.selectVoiture(0);
    Test.setWidth(route.getLargeurVoiePlateau() - 15);
    Test.calculerHauteur();
    Test.placer(LEVEL_WIDTH/2, LEVEL_HEIGHT - Test.getHeight() - 50);
    Test.vitesse = 10;
}

Partie::~Partie()
{
    //dtor
}

void Partie::play()
{
    gestion_touches();
    deplacements();
    afficher();
}

void Partie::gestion_touches()
{
    SDL_Event event;
    calculerEchelle();
    while( SDL_PollEvent( &event ) != 0 )
    {
        //Fermer la fenêtre
        if(event.type == SDL_QUIT)
        {
            jouer = false;

        }
        //Evenements de fenêtre
        if(event.type == SDL_WINDOWEVENT)
        {
            switch (event.window.event)
            {
            case SDL_WINDOWEVENT_SIZE_CHANGED:
                SCREEN_WIDTH = event.window.data1;
                SCREEN_HEIGHT = event.window.data2;
                break;

            case SDL_WINDOWEVENT_FOCUS_LOST:
                if(not pause)
                    //pause = true;
                break;
            }

        }

        Test.gestionTouches( event );

        // Les touches
        if( event.type == SDL_KEYDOWN && event.key.repeat == 0 )
        {
            switch( event.key.keysym.sym )
            {
                case 'p':
                    if(pause)
                        pause = false;
                    else
                        pause = true;
                    break;

                case 'm' :
                    jouer = false;

                // Déplacement de la caméra
                case 'q':
                    camera.x -= 100;
                    break;

                case 'd':
                    camera.x += 100;
                    break;

                case 'z':
                    camera.y -= 100;
                    break;

                case 's':
                    camera.y += 100;
                    break;

                case 'a' :
                    camera.w += 50;
                    camera.h += 50;
                    break;

                case 'e':
                    camera.w -= 50;
                    camera.h -= 50;
                    break;

                //Afficher la route centrée à l'echelle 1
                case 'r':
                    camera.w = SCREEN_WIDTH;
                    camera.h = SCREEN_HEIGHT;
                    calculerEchelle();
                    camera.x = (route.getPosX() * echelle) - ((SCREEN_WIDTH - route.calculerLargeurDansFenetre())/2); // Fonction
                    camera.y = LEVEL_HEIGHT - SCREEN_HEIGHT;
                    break;

                // Afficher tout le plateau
                case 't' :
                    camera.w = LEVEL_WIDTH;
                    camera.h = LEVEL_HEIGHT;
                    calculerEchelle();
                    camera.x = 0;
                    camera.y = (plateau.calculerHauteurDansFenetre() - SCREEN_HEIGHT)/2;
                    break;

                //Afficher toute la hauteur de la route
                case 'y' :
                    camera.h = LEVEL_HEIGHT;
                    camera.w = LEVEL_HEIGHT * ((float)SCREEN_WIDTH/(float)SCREEN_HEIGHT);
                    calculerEchelle();
                    camera.x = (route.getPosX() * echelle) - ((SCREEN_WIDTH - route.calculerLargeurDansFenetre())/2); // Fonction
                    camera.y = 0;


                default:
                    break;
            }
        }
    }
}

void Partie::deplacements()
{
    if (timerDeplacement.getTicks() > 10 and not pause) // changer ce compteur
    {

        //Déplacement de la route
        route.deplacer(Test.vitesse);

        //Déplacement des décors
        decor_gestionnaire.gestion(Test.vitesse);

        //Déplacement des voitures
        voiture_gestionnaire.chargement_voitures_fichier(&route);
        voiture_gestionnaire.depassement(route);
        if ( voiture_gestionnaire.gestion_voitures(Test.vitesse, Test.getObjet()) )
        {
            Test.eventCollision();
        }

        Test.deplacer(route.getObjet());

        timerDeplacement.start();
    }
}


void Partie::calculerEchelle()
{
    echelle = (float)SCREEN_WIDTH / (float)camera.w;
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
    SDL_SetRenderDrawColor(pRenderer, 0, 0, 255, 150);
    //route.afficherRectObjet();
    SDL_SetRenderDrawColor(pRenderer, 0, 255, 0, 255);
    //route.afficherVoies();

    //Affichage des voitures
    voiture_gestionnaire.afficherVoitures(carsTexture);

    //Affichage voiture joueur
    Test.afficher(carsTexture);
    SDL_SetRenderDrawColor(pRenderer, 0, 0, 255, 120);
    Test.afficherRectCollision();

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


    if (pause)
    {
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

bool Partie::continuer_partie()
{
    return jouer;
}
