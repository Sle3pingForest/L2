#include "Partie.hpp"

using namespace std;

std::ifstream infile("autres/niveau1");

Partie::Partie()
{
    jouer = true;
    decorTexture = LoadBmpWithTransparency("autres/images/decor.bmp", 0, 255, 255);
    carsTexture = LoadBmpWithTransparency("autres/images/cars.bmp", 0, 255, 255);
    roadTexture = LoadBmpWithTransparency("autres/images/road.bmp", 0, 255, 255);

    voiture_joueur.setWidth(route.getLargeurVoie() - 15);
    voiture_joueur.setHeight(150);
    voiture_joueur.placer(SCREEN_WIDTH/2, SCREEN_HEIGHT-voiture_joueur.getHeight()- SCREEN_HEIGHT/50); //Fixer le 20

    placer_Decors();

    timerFPS.start();
    timerDeplacement.start();
    vitesse = 0;
}

Partie::~Partie()
{
    //dtor
}

void Partie::placer_Decors() //Place les décors une première fois
{
    int posY = 0;
    for(int i = 0 ; i < 9; i++)
    {
        tabDecor[i].selectDecor(1, i);
        tabDecor[i].placer((i%2)*70, posY);
        if (i%2)
        {
            posY += 120;
        }
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
                    pause = true;
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

                case 'q':
                    jouer = false;
                    break;

                default:
                    break;
            }
        }

    }
}

void Partie::gestion_collisions()
{
    for(int i = 0 ; i < 10; i++)
    {
        if(collision(voiture_joueur, tabVoiture[i]))
        {
            vitesse = 3;
        }
    }
}

bool Partie::collision(Voiture R1, Voiture R2)
{
    int leftR1 = R1.getPosX();
    int leftR2 = R2.getPosX();
    int rightR1 = R1.getPosX() + R1.getWidth();
    int rightR2 = R2.getPosX() + R2.getWidth();
    int topR1 = R1.getPosY();
    int topR2 = R2.getPosY();
    int bottomR1 = R1.getPosY() + R1.getHeight();
    int bottomR2 = R2.getPosY() + R2.getHeight();
    bool toucher = false;
    if(rightR1 >= leftR2 && rightR1 <= rightR2 && topR1 >= topR2 && topR1 <= bottomR2)
    {
        cout<< "Collision cote a gauche: "<<endl;
        cout<< "X joueur: "<<rightR1 <<" Y joueur: "<< topR1 <<endl;
        toucher = true;
    }
    else if(leftR1 >= leftR2 && leftR1 <= rightR2 && topR1 >= topR2 && topR1 <= bottomR2)
    {
        cout<< "Collision cote a gauche: "<<endl;
        cout<< "X joueur: "<<leftR1 <<" Y joueur: "<< topR1 <<endl;
        toucher = true;
    }
    else if(leftR1 >= leftR2 && leftR1 <= rightR2 && bottomR1 >= topR2 && bottomR1 <= bottomR2)
    {
        cout<< "Collision cote a gauche: "<<endl;
        cout<< "X joueur: "<<leftR1 <<" Y joueur: "<< bottomR1 <<endl;
        toucher = true;
    }
    else if(rightR1 >= leftR2 && rightR1 <= rightR2 && bottomR1 >= topR2 && bottomR1 <= bottomR2)
    {
        cout<< "Collision cote a gauche: "<<endl;
        cout<< "X joueur: "<<rightR1 <<" Y joueur: "<< bottomR1 <<endl;
        toucher = true;
    }
    else
    {
        toucher = false;
    }
    return toucher;
}

void Partie::chargement_voitures_fichier()
{
    string line;
    if(tabVoiture[0].getPosY() > SCREEN_HEIGHT)
    {
        int cpt = 0;
        for(int i = 0 ; i < 4; ++i)
        {
            getline(infile, line);

            for( int j = 0 ; j < 4 ; ++j)
            {
                if(line[j] == '1')
                {
                    tabVoiture[cpt].setWidth(route.getLargeurVoie() - 15);
                    tabVoiture[cpt].setHeight(150);
                    int position = route.getPosX() + j *route.getLargeurVoie() +7;
                    tabVoiture[cpt].placer(position, -200 + i*50); // Fixer les tailles
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

        //Déplacement des décors
        for(int i = 0 ; i < 9; i++)
        {
            if(tabDecor[i].getPosY() > SCREEN_HEIGHT)
            {
                tabDecor[i].placer(tabDecor[i].getPosX(), 0 - tabDecor[i].getHeight() ) ;
            }
            tabDecor[i].deplacer(0, vitesse);
        }
        timerDeplacement.start();
    }
}

void Partie::afficher()
{
    if (timerFPS.getTicks() >= 1000/SCREEN_FPS)
    {
        //Création de la couleur de fond
        SDL_SetRenderDrawColor(pRenderer, 88, 41, 0, 255);
        SDL_RenderClear(pRenderer);

        //Affichage de la route
        route.afficher(roadTexture);

        route.afficherVoies();

        //Affichages des décors
        for(int i = 0 ; i < 9; i++)
        {
            tabDecor[i].afficher(decorTexture);
        }

        //Affichage des voitures
        for(int i = 0 ; i < 4; i++)
        {
            tabVoiture[i].afficher(carsTexture);
        }

        //Affichage voiture joueur
        voiture_joueur.afficher(carsTexture);

        SDL_RenderPresent(pRenderer);

        FPS++;
        timerFPS.start();
    }
}

bool Partie::continuer_partie()
{
    return jouer;
}
