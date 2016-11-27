#include "Menu.hpp"

/* Jouer High score Quitter*/

SDL_Window *pWindow =NULL;
SDL_Renderer *pRenderer = NULL;

int SCREEN_WIDTH = 700;
int SCREEN_HEIGHT = 700;
int SCREEN_FPS = 60;

Menu::Menu()
{
    quit = false;
    choix = 1;
}

Menu::~Menu()
{
    SDL_DestroyRenderer(pRenderer);
    SDL_DestroyWindow(pWindow);
    SDL_Quit();
}

bool Menu::InitSDL()
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0 ) {
        fprintf(stderr,"Échec de l'initialisation de la SDL (%s)\n",SDL_GetError());
        return false;
    }
    pWindow = SDL_CreateWindow("TrafficRacer", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_RESIZABLE);
    if( !pWindow ) {
        fprintf(stderr,"Erreur de création de la fenêtre: %s\n",SDL_GetError());
        return false;
    }
    pRenderer =  SDL_CreateRenderer( pWindow, -1, SDL_RENDERER_ACCELERATED );
    if( !pRenderer ) {
        fprintf(stderr, "Échec de la création du rendu: %s\n", SDL_GetError());
        return false;
    }
    return true;
}

void Menu::boucle()
{
    affichage();
    while (!quit) {
        gestion_touches();
        SDL_Delay(100);
    }
}

void Menu::gestion_touches()
{
    SDL_Event event;
    while( SDL_PollEvent( &event ) != 0 )
    {
        //Fermer la fenêtre
        if(event.type == SDL_QUIT) {
            quit = true;
        }
        
        //Evenements de fenêtre
        if(event.type == SDL_WINDOWEVENT) {
            switch (event.window.event) {
                case SDL_WINDOWEVENT_SIZE_CHANGED:
                    SCREEN_WIDTH = event.window.data1;
                    SCREEN_HEIGHT = event.window.data2;
                    affichage();
                    break;
            }
        }
        
        if(event.type == SDL_KEYDOWN) {
            switch( event.key.keysym.sym ) {
                case SDLK_UP:
                    if(choix == 1)
                        choix = 3;
                    else
                        choix--;
                    affichage();
                    break;
                    
                case SDLK_DOWN:
                    if(choix == 3)
                        choix = 1;
                    else
                        choix++;
                    affichage();
                    break;
                    
                case SDLK_RETURN:
                    execute();
                    
                default:
                    break;
            }
        }
    }
}

void Menu::affichage()
{
    SDL_SetRenderDrawColor(pRenderer, 40, 40, 40, 255);
    SDL_RenderClear(pRenderer);
    SDL_Rect Test = {0,0,100,100};
    if(choix == 1)
        SDL_SetRenderDrawColor(pRenderer, 255, 0, 0, 255);
    else if(choix == 2)
        SDL_SetRenderDrawColor(pRenderer, 0, 255, 0, 255);
    else
        SDL_SetRenderDrawColor(pRenderer, 0, 0, 255, 255);
    SDL_RenderFillRect(pRenderer, &Test);
    SDL_RenderPresent(pRenderer);
}

void Menu::execute()
{
    if(choix == 1) {
        Partie* pPartie;
        pPartie = new Partie;
        pPartie->play();
        delete pPartie;
        pPartie = NULL;
        affichage();
        //quit = true;
    }
    else if(choix == 2)
        quit = true;
    else
        quit = true;
}
