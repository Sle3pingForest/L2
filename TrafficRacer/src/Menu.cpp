#include "Menu.hpp"

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

void Menu::chargementsImages() {
    logoTexture = LoadBmpWithTransparency("autres/images/logo.bmp", 0, 255, 255);
    scoreTexture = LoadBmpWithTransparency("autres/images/number.bmp", 0, 255, 0);
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
    SDL_SetRenderDrawBlendMode(pRenderer, SDL_BLENDMODE_BLEND);
    return true;
}

void Menu::boucle()
{
    chargementsImages();
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
    
    SDL_Rect logo;
    logo.w = SCREEN_WIDTH*0.8;
    if(logo.w > 900){
        logo.w = 900;
    }
    logo.h = logo.w / 4.3;
    logo.x = (SCREEN_WIDTH - logo.w) / 2;
    logo.y = SCREEN_HEIGHT * 0.1;
    SDL_RenderCopy(pRenderer, logoTexture, NULL, &logo);
    
    if(choix == 1) {
        logo.y += logo.h;
        SDL_RenderCopy(pRenderer, logoTexture, NULL, &logo);
    }
    else if(choix == 2) {
        logo.y += 2 * logo.h;
        SDL_RenderCopy(pRenderer, logoTexture, NULL, &logo);
    }
    else {
        logo.y += 3 * logo.h;
        SDL_RenderCopy(pRenderer, logoTexture, NULL, &logo);
    }
    SDL_RenderPresent(pRenderer);
}

void Menu::execute()
{
    if(choix == 1) {
        Partie* pPartie;
        pPartie = new Partie;
        //int score =
        pPartie->play();
        delete pPartie;
        pPartie = NULL;
        affichage();
    }
    else if(choix == 2) {
        affichageScore();
    }
    else
        quit = true;
}

void Menu::affichageScore()
{
    int j = 0;
    std::ifstream fichier;
    fichier.open("autres/score", ios::in);
    string line;
    int PosY = 0;
    while(getline(fichier, line)) {
        cout<<"ligne :"<<line<<endl;
        int PosX = 0;
        while (line[j] != '\0') {
            printf("%c", line[j]);
            afficherChiffre(line[j], 120, PosX, PosY);
            PosX += 100;
            j++;
        }
        printf("\n");
        PosY += 130;
    }
    fichier.close();
    SDL_RenderPresent(pRenderer);
}

SDL_Texture* Menu::LoadBmpWithTransparency(const char* emplacement, Uint8 redTransparency, Uint8 greenTransparency, Uint8 blueTransparency)
{
    SDL_Surface *loadedImage = NULL;
    SDL_Texture *texture = NULL;
    
    loadedImage = SDL_LoadBMP(emplacement);
    
    if(loadedImage != NULL) {
        Uint32 colorkey = SDL_MapRGB( loadedImage->format, redTransparency, greenTransparency, blueTransparency);
        SDL_SetColorKey(loadedImage, SDL_TRUE, colorkey);
        texture = SDL_CreateTextureFromSurface(pRenderer, loadedImage);
        if(texture == NULL) {
            fprintf(stderr, "Échec de la création de la texture de l'image: %s\n", SDL_GetError());
        }
        SDL_FreeSurface(loadedImage);
        return texture;
    } else {
        fprintf(stderr, "Échec du chargement de l'image: %s\n", SDL_GetError());
        return NULL;
    }
}

void Menu::afficherChiffre(char chiffre, int HauteurPolice, int PosX, int PosY) {
    int intChiffre = chiffre - 48;
    SDL_Rect dest;
    dest.x = PosX;
    dest.y = PosY;
    dest.h = HauteurPolice;
    dest.w = HauteurPolice / 1.6;
    
    SDL_Rect selection;
    selection.y = 0;
    selection.w = 90;
    selection.h = 144;
    selection.x = (intChiffre * 91) + intChiffre;
    
    SDL_RenderCopy(pRenderer, scoreTexture, &selection, &dest);
}

void Menu::afficherNombre(int nombre, int HauteurPolice, int PosX, int PosY) {
    int unite = nombre % 10;
    int dizaine = nombre / 10 % 10;
    int centaine = nombre / 100 % 10;
    int milier = nombre / 1000 % 10;
    
    int largeur = HauteurPolice / 1.6;
    
    afficherChiffre(milier,HauteurPolice,PosX,PosY);
    afficherChiffre(centaine,HauteurPolice,PosX+largeur+5,PosY);
    afficherChiffre(dizaine,HauteurPolice,PosX+(2*(largeur+5)),PosY);
    afficherChiffre(unite,HauteurPolice,PosX+(3*(largeur+5)),PosY);
    
}
