#include "Partie.hpp"

using namespace std;
std::ifstream infile("autres/niveau1");

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
    testTexture = LoadBmpWithTransparency("autres/images/test.bmp", 0, 255, 255);

    voiture_joueur.selectVoiture(0);
    voiture_joueur.setWidth(route.getLargeurVoiePlateau() - 15);
    voiture_joueur.calculerHauteur();
    voiture_joueur.placer(LEVEL_WIDTH/2, LEVEL_HEIGHT - voiture_joueur.getHeight() - 50);

    //Placer les Decors
    for (int i = 0; i < 30; ++i)
    {
        tab[i] = new Decor(rand()%LEVEL_WIDTH, rand()%LEVEL_HEIGHT - LEVEL_HEIGHT);
        tab[i]->selectDecor(1, rand()%9);
    }

    timerFPS.start();
    timerDeplacement.start();
    vitesse = 10;
    
    tabVoiture[0].setPosY(SCREEN_HEIGHT+1);
    
    SDL_SetRenderDrawBlendMode(pRenderer, SDL_BLENDMODE_BLEND);
//////////////////////////////////////////////
    plateau.placer(0, 0);
    plateau.setWidth(LEVEL_WIDTH);
    plateau.setHeight(LEVEL_HEIGHT);
    
    //Initialisation de la position de la caméra
    camera.w = LEVEL_WIDTH;
    camera.h = LEVEL_HEIGHT;
    calculerEchelle();
    camera.x = 0;
    camera.y = (plateau.calculerHauteurDansFenetre() - SCREEN_HEIGHT)/2;
//////////////////////////////////////////////
    
}

Partie::~Partie()
{
    //dtor
    for (int i = 0; i < 30; ++i)
    {
        delete tab[i];
    }
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

        // Les touches
        else if( event.type == SDL_KEYDOWN )
        {
            switch( event.key.keysym.sym )
            {
                case SDLK_UP:
                    vitesse += 1;
                    if(vitesse > 20)
                        vitesse = 20;
                    break;

                case SDLK_DOWN:
                    vitesse -= 2;
                    if(vitesse < 0)
                        vitesse = 0;
                    break;

                case SDLK_LEFT:
                    voiture_joueur.deplacer(-25, 0);
                    if(voiture_joueur.getPosX() <= route.getPosX())
                    {
                        voiture_joueur.placer(route.getPosX(), voiture_joueur.getPosY());
                        vitesse -= 5;
                        if(vitesse < 0)
                            vitesse = 0;
                    }
                    break;

                case SDLK_RIGHT:
                    voiture_joueur.deplacer(+25, 0);
                    if(voiture_joueur.getPosX() + voiture_joueur.getWidth() >= route.getPosX() + route.getWidth())
                    {
                        voiture_joueur.placer(route.getPosX() + route.getWidth() - voiture_joueur.getWidth() , voiture_joueur.getPosY());
                        vitesse -= 5;
                        if(vitesse < 0)
                            vitesse = 0;
                    }
                    break;
                    
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

void Partie::gestion_collisions()
{
    SDL_bool collision;
    SDL_Rect intersect;
    for(int i = 0 ; i < 10; i++)
    {
        collision = SDL_IntersectRect(voiture_joueur.getObjet(), tabVoiture[i].getObjet(), &intersect);
        if (collision)
        {
            vitesse = 3;
        }
    }
}

void Partie::chargement_voitures_fichier()
{
    if(tabVoiture[0].getPosY() > SCREEN_HEIGHT)
    {
        string line;
        int cpt = 0;
        for(int i = 0 ; i < 4; ++i)
        {
            getline(infile, line);

            for( int j = 0 ; j < 4 ; ++j)
            {
                if(line[j] == '1')
                {
                    tabVoiture[cpt].selectVoiture(rand()%8);
                    tabVoiture[cpt].setWidth(route.getLargeurVoiePlateau() - 15);
                    tabVoiture[cpt].calculerHauteur();
                    int position_x = route.getPosX() + j *route.getLargeurVoiePlateau() + rand()%10;
                    int position_y = i*(tabVoiture[cpt].getHeight() + 50) - LEVEL_HEIGHT; // Fixer les tailles
                    tabVoiture[cpt].placer(position_x, position_y);
                    cpt++;
                }
            }
        }
    }
}

void Partie::deplacements()
{
    if (timerDeplacement.getTicks() > 10 and not pause) // changer ce compteur
    {
        int vitesseAutresVoitures = 8;

        //Déplacement de la route
        route.deplacer(vitesse);

        //Déplacement des voitures
        for(int i = 0 ; i < 4; i++)
        {
            tabVoiture[i].deplacer(0, vitesse - vitesseAutresVoitures );
        }

        gestion_decors();
        timerDeplacement.start();
    }
}

void Partie::gestion_decors()
{
    for (int i = 0; i < 30; ++i)
    {
        if (tab[i]->isDead())
        {
            delete tab[i];
            tab[i] = new Decor(rand()%LEVEL_WIDTH, rand()%LEVEL_HEIGHT - LEVEL_HEIGHT);
            tab[i]->selectDecor(1, rand()%9);
        }
        tab[i]->deplacer(0, vitesse);
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
    
    //SDL_Rect plateauDest = plateau.calculerPosFenetre();
    //SDL_RenderCopy(pRenderer, testTexture, NULL, &plateauDest);

    
    //Affichages des décors
    for(int i = 0 ; i < 30; i++)
    {
        if (tab[i] != NULL)
        {
            tab[i]->afficher(decorTexture);
        }
    }
    
    //Affichage de la route
    //route.afficher(routeTexture);
    SDL_SetRenderDrawColor(pRenderer, 0, 0, 255, 150);
    route.afficherRectObjet();
    SDL_SetRenderDrawColor(pRenderer, 0, 255, 0, 255);
    route.afficherVoies();
    
    //Affichage des voitures
    for(int i = 0 ; i < 4; i++)
    {
        tabVoiture[i].afficher(carsTexture);
    }
    
    //Affichage voiture joueur
    voiture_joueur.afficher(carsTexture);
    
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
