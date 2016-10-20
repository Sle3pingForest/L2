#include "Partie.hpp"


using namespace std;

std::ifstream infile("autres/niveau1");

Partie::Partie()
{
    jouer = true;
    decorTexture = LoadBmpWithTransparency("autres/images/decor.bmp", 0, 255, 255);
    carsTexture = LoadBmpWithTransparency("autres/images/cars.bmp", 0, 255, 255);
    roadTexture = LoadBmpWithTransparency("autres/images/road.bmp", 0, 255, 255);

    voiture_joueur.setWeight(route.getLargeurVoie() - 15);
    voiture_joueur.setHeight(150);
    voiture_joueur.placer(SCREEN_WIDTH/2, SCREEN_HEIGHT-voiture_joueur.getCarHeight()-20); //Fixer le 20
    gestion_decor(true);
    timerFPS.start();

    vitesse = 0;
}

Partie::~Partie()
{
    //dtor
}

void Partie::gestion_touches()
{
    SDL_Event event;
    while( SDL_PollEvent( &event ) != 0 )
    {
        //Fermer la fenêtre
        if (event.type == SDL_QUIT)
        {
            jouer = false;

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
                if(voiture_joueur.getPosX() <= route.getPositionXRoad())
                {
                    voiture_joueur.placer(route.getPositionXRoad(), voiture_joueur.getPosY());
                }
                break;

            case SDLK_RIGHT:

                voiture_joueur.deplacer(+25, 0);
                if(voiture_joueur.getPosX() + voiture_joueur.getCarWidth() >= route.getPositionXRoad() + route.getWeightRoad())
                {
                    voiture_joueur.placer(route.getPositionXRoad() + route.getWeightRoad() - voiture_joueur.getCarWidth() , voiture_joueur.getPosY());
                }
                break;

            default:
                break;
            }
        }

    }
}

void Partie::gestion_decor(bool init)
{
    int posY = 0;
    for(int i = 0 ; i < 9; i++)
    {
        if(init)
        {
            tabDecor[i].selectDecor(1, i);
            tabDecor[i].placer((i%2)*70, posY);
            if (i%2) {
                posY += 120;
            }
        }
        else
        {
            if(tabDecor[i].getPosY() > SCREEN_HEIGHT)
                tabDecor[i].placer(tabDecor[i].getPosX(), 0 - tabDecor[i].getDecorHeight() ) ;

            tabDecor[i].deplacer(0, vitesse);
            tabDecor[i].afficher(decorTexture);
        }
    }
}

bool Partie::colission(Voiture R1, Voiture R2)
{
     int leftR1 = R1.getPosX();
     int leftR2 = R2.getPosX();
     int rightR1 = R1.getPosX() + R1.getCarWidth();
     int rightR2 = R2.getPosX() + R2.getCarWidth();
     int topR1 = R1.getPosY();
     int topR2 = R2.getPosY();
     int bottomR1 = R1.getPosY() + R1.getCarHeight();
     int bottomR2 = R2.getPosY() + R2.getCarHeight();
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

void Partie::afficher()
{

    if (timerFPS.getTicks() > 1000/SCREEN_FPS)
    {

        string line;

        //Création de la couleur de fond
        SDL_SetRenderDrawColor(pRenderer, 88, 41, 0, 255);
        SDL_RenderClear(pRenderer);


        //route.AfficherRoute();
        route.afficher(roadTexture, vitesse);

        gestion_decor(false);

        // Gestion des déplacement, faire des fonctions

        if(tabVoiture[0].getPosY() > SCREEN_HEIGHT)
        {
            int cpt = 0;
            for(int i = 0 ; i < 4; ++i)
            {
                getline(infile, line);
                cout<< line<< endl;

                for( int j = 0 ;j < 4 ; ++j)
                {
                    if(line[j] == '1')
                    {
                        tabVoiture[cpt].setWeight(90);
                        tabVoiture[cpt].setHeight(150);
                        int position = route.getPositionXRoad() + j *route.getLargeurVoie();
                        tabVoiture[cpt].placer(position, -200 + i*50);
                        cout<<cpt+1<< endl;
                        cpt++;
                    }
                }
            }

        }

        //Affichage des voitures
        for(int i = 0 ; i < 4; i++)
        {

            SDL_SetRenderDrawColor(pRenderer, 255, 0, 0, 0);
            tabVoiture[i].afficher(carsTexture);
            tabVoiture[i].deplacer(0,5);
        }

        //Gestion des collisions
        for(int i = 0 ; i < 10; i++)
        {
            if(colission(voiture_joueur, tabVoiture[i]))
            {
                SDL_Delay(10);
            }
        }

        SDL_SetRenderDrawColor(pRenderer, 100, 180, 70, 0);
        //voiture_joueur.AfficherVoiture();
        voiture_joueur.afficher(carsTexture);
        SDL_RenderPresent(pRenderer);

        timerFPS.start();
    }
}

bool Partie::continuer_partie()
{
    return jouer;
}
