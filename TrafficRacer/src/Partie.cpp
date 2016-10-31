#include "Partie.hpp"

using namespace std;
std::ifstream infile("autres/niveau1");

int LEVEL_WIDTH = 2000;
int LEVEL_HEIGHT = 1200;

SDL_Rect camera;
float echelle;

Partie::Partie()
{
    jouer = true;
    pause = false;
    
    decorTexture = LoadBmpWithTransparency("autres/images/decor.bmp", 0, 255, 255);
    carsTexture = LoadBmpWithTransparency("autres/images/cars.bmp", 0, 55, 255);
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
    vitesse = SCREEN_HEIGHT/50;
    
    tabVoiture[0].setPosY(SCREEN_HEIGHT+1);
    
    SDL_SetRenderDrawBlendMode(pRenderer, SDL_BLENDMODE_BLEND);
//////////////////////////////////////////////
    plateau.placer(0, 0);
    plateau.setWidth(LEVEL_WIDTH);
    plateau.setHeight(LEVEL_HEIGHT);
    
    camera.x = 1000;
    camera.y = 0;
    camera.w = SCREEN_WIDTH;
    camera.h = SCREEN_HEIGHT;
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
//                case SDLK_UP:
//                    vitesse += 1;
//                    if(vitesse > 20)
//                        vitesse = 20;
//                    break;
//
//                case SDLK_DOWN:
//                    vitesse -= 2;
//                    if(vitesse < 0)
//                        vitesse = 0;
//                    break;
//
//                case SDLK_LEFT:
//                    voiture_joueur.deplacer(-25, 0);
//                    if(voiture_joueur.getPosX() <= route.getPosX())
//                    {
//                        voiture_joueur.placer(route.getPosX(), voiture_joueur.getPosY());
//                        vitesse -= 5;
//                        if(vitesse < 0)
//                            vitesse = 0;
//                    }
//                    break;
//
//                case SDLK_RIGHT:
//                    voiture_joueur.deplacer(+25, 0);
//                    if(voiture_joueur.getPosX() + voiture_joueur.getWidth() >= route.getPosX() + route.getWidth())
//                    {
//                        voiture_joueur.placer(route.getPosX() + route.getWidth() - voiture_joueur.getWidth() , voiture_joueur.getPosY());
//                        vitesse -= 5;
//                        if(vitesse < 0)
//                            vitesse = 0;
//                    }
//                    break;

                case 'p':
                    if(pause)
                        pause = false;
                    else
                        pause = true;
                    break;
                    
                case 'm' :
                    jouer = false;

                // Déplacement de la caméra
                //case 'q':
                case SDLK_LEFT:
                    camera.x -= 100;
                    break;
                    
                //case 'd':
                case SDLK_RIGHT:
                    camera.x += 100;
                    break;
                    
                //case 'z':
                case SDLK_UP:
                    camera.y -= 100;
                    break;
                    
                //case 's':
                case SDLK_DOWN :
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
                    
                case 'r':
                    camera.w = SCREEN_WIDTH;
                    camera.h = SCREEN_HEIGHT;
                    break;

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
                    int position = route.getPosX() + j *route.getLargeurVoiePlateau() +7;
                    tabVoiture[cpt].placer(position, i*(tabVoiture[cpt].getHeight() + 50) - SCREEN_HEIGHT); // Fixer les tailles
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

void Partie::afficher()
{
    
    //Création de la couleur de fond
    SDL_SetRenderDrawColor(pRenderer, 88, 41, 0, 0);
    SDL_RenderClear(pRenderer);
    


    
    //Affichage des voitures
    for(int i = 0 ; i < 4; i++)
    {
        tabVoiture[i].afficher(carsTexture);
    }
    
    
    
/////// TEST ROUTE 2000x1200  /////////////
    
    //Faire Fonction
    echelle = (float)SCREEN_WIDTH / (float)camera.w;
    //
    
    //Déplace le plateau en foncton de la caméra
    SDL_Rect plateauDest = plateau.calculerPosFenetre();
    SDL_RenderCopy(pRenderer, testTexture, NULL, &plateauDest);

    
    //Affichages des décors
    for(int i = 0 ; i < 30; i++)
    {
        if (tab[i] != NULL)
        {
            tab[i]->afficher(decorTexture);
        }
    }
    
    //Affichage de la route
    route.afficher(routeTexture);
    SDL_SetRenderDrawColor(pRenderer, 0, 0, 255, 150);
    route.afficherRectObjet();
    SDL_SetRenderDrawColor(pRenderer, 0, 255, 0, 255);
    route.afficherVoies();
    
    //Affichage voiture joueur
    voiture_joueur.afficher(carsTexture);
    
    Decor testdec;
    testdec.placer(200, 200);
    testdec.selectDecor(1, 3);
    testdec.afficher(decorTexture);
    
    Objet test;
    test.placer(1000, 500);
    test.setWidth(route.getWidth()/4);
    test.setHeight(250);
    test.afficherRectObjet();
    
    Voiture testvoit;
    testvoit.selectVoiture(0);
    testvoit.placer(200, 200);
    testvoit.afficherRectObjet();
    testvoit.afficher(carsTexture);
    
    
    
/////// FIN ROUTE 2000x1200  /////////////
    
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
