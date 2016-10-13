#include "Partie.hpp"


using namespace std;

std::ifstream infile("autres/niveau1");

Partie::Partie()
{
    jouer = true;
    decorTexture = LoadBmpWithTransparency("autres/images/decor.bmp", 00, 255, 255);

    voiture_joueur.placer(SCREEN_WIDTH/2, SCREEN_HEIGHT-voiture_joueur.getCarHeight()-20); //Fixer le 20
    tabDecor[0].placer(-70, 0);
    tabDecor[1].placer(SCREEN_WIDTH-130, 250);
    tabDecor[2].placer(-10, 400);
}

Partie::~Partie()
{
    //dtor
}

void Partie::gestion_evenements()
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
                    break;

            case SDLK_DOWN:
                break;

            case SDLK_LEFT:
                voiture_joueur.deplacer(-25, 0);
                break;

            case SDLK_RIGHT:
                voiture_joueur.deplacer(+25, 0);
                break;

            default:
                break;
            }
        }

    }
}

void Partie::afficher()
{
    const int FPS = 60;
    Uint32 start;
    start = SDL_GetTicks();
    string line;

    //Création de la couleur de fond
    SDL_SetRenderDrawColor(pRenderer, 88, 41, 0, 255);
    SDL_RenderClear(pRenderer);

    route.AfficherRoute();


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
                    int position = route.getPositionXRoad() + j *route.getLargeurVoie();
                    tabVoiture[cpt].placer(position, -200 + i*50);
                    cout<<cpt+1<< endl;
                    cpt++;
               }
            }
        }

    }


    for(int i = 0 ; i < 4; i++)
    {

        if(tabDecor[i].getPosY() > SCREEN_HEIGHT)
            tabDecor[i].placer(tabDecor[i].getPosX(), 0 - tabDecor[i].getDecorHeight() ) ;

        tabDecor[i].afficher(decorTexture);
        tabDecor[i].deplacer(0,10);

        SDL_SetRenderDrawColor(pRenderer, 255, 0, 0, 0);
        tabVoiture[i].AfficherVoiture();
        tabVoiture[i].deplacer(0,1);
    }
    //Gestion des collisions
    for(int i = 0 ; i < 10; i++)
    {
        if(tabVoiture[i].getPosY()+tabVoiture[i].getCarHeight() == voiture_joueur.getPosY()) // Si la voiture est à la même hauteur que celle du joueur
        {
            int posJoueurGauche = voiture_joueur.getPosX();
            int posJoueurDroit = voiture_joueur.getPosX() + voiture_joueur.getCarWidth();
            int posVoitureGauche = tabVoiture[i].getPosX();
            int posVoitureDroit = tabVoiture[i].getPosX() + tabVoiture[i].getCarWidth();
            if( (posJoueurGauche >= posVoitureGauche and posJoueurGauche <= posVoitureDroit) or (posJoueurDroit >= posVoitureGauche and posJoueurDroit <= posVoitureDroit) ) // Si la voiture est en face de celle du joueur PAS FINI
            {
                fprintf(stderr,"Collision voiture %d\n", i);
                SDL_RenderPresent(pRenderer);
                SDL_Delay(200);
            }
        }
    }

    SDL_SetRenderDrawColor(pRenderer, 100, 180, 70, 0);
    voiture_joueur.AfficherVoiture();
    SDL_RenderPresent(pRenderer);

    //Calcul du temps à attendre les FPS
    if(1000/FPS > SDL_GetTicks()-start)
    {
        SDL_Delay(1000/FPS-(SDL_GetTicks()-start));
    }
}

bool Partie::continuer_partie()
{
    return jouer;
}
