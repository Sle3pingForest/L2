#include "Menu.hpp"

#include <string>
using namespace std;

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

bool Menu::Init()
{
    return InitSDL();
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

void Menu::chargementsImages() {
    logoTexture = LoadBmpWithTransparency("autres/images/logo.bmp", 0, 255, 255);
    numberTexture = LoadBmpWithTransparency("autres/images/number.bmp", 0, 255, 0);
    playTexture = LoadBmpWithTransparency("autres/images/play.bmp", 0, 255, 255);
    hscoreTexture = LoadBmpWithTransparency("autres/images/score.bmp", 0, 255, 255);
    exitTexture = LoadBmpWithTransparency("autres/images/exit.bmp", 0, 255, 255);
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
    SDL_SetRenderDrawColor(pRenderer, 60, 60, 60, 255);
    SDL_RenderClear(pRenderer);

    SDL_Rect logo;
    logo.w = SCREEN_WIDTH * 0.8;
    if(logo.w > 900) {
        logo.w = 900;
    }
    logo.h = logo.w / 4.3;
    logo.x = (SCREEN_WIDTH - logo.w) / 2;
    logo.y = SCREEN_HEIGHT * 0.1;
    SDL_RenderCopy(pRenderer, logoTexture, NULL, &logo);

    logo.w = logo.w * 0.5;
    logo.h = logo.w / 3.75;
    logo.x = (SCREEN_WIDTH - logo.w) / 2;

    if(choix == 1) {
        SDL_SetTextureAlphaMod(playTexture, 255);
        SDL_SetTextureAlphaMod(hscoreTexture, 120);
        SDL_SetTextureAlphaMod(exitTexture, 120);
    }

    else if (choix == 2) {
        SDL_SetTextureAlphaMod(playTexture, 120);
        SDL_SetTextureAlphaMod(hscoreTexture, 255);
        SDL_SetTextureAlphaMod(exitTexture, 120);
    } else {
        SDL_SetTextureAlphaMod(playTexture, 120);
        SDL_SetTextureAlphaMod(hscoreTexture, 120);
        SDL_SetTextureAlphaMod(exitTexture, 255);
    }

    logo.y += SCREEN_HEIGHT / 3;
    SDL_RenderCopy(pRenderer, playTexture, NULL, &logo);
    logo.y += logo.h * 1.25;
    SDL_RenderCopy(pRenderer, hscoreTexture, NULL, &logo);
    logo.y += logo.h * 1.25;
    SDL_RenderCopy(pRenderer, exitTexture, NULL, &logo);
    SDL_RenderPresent(pRenderer);
}

void Menu::execute()
{
    if(choix == 1) {
        Partie* pPartie;
        pPartie = new Partie;
        int score = pPartie->play();
        setScore(score);
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


void Menu::ordonnerScore_Top5(int New_Score, int top5[5])
{
    int pos = 0;
    int min_valeur = top5[0];

    for(int i = 0; i < 5; ++i)
    {
        if( top5[i]<= min_valeur)
        {
            min_valeur = top5[i];
            pos = i;
        }
    }
    if( top5[pos] < New_Score )
    {
        top5[pos] = New_Score;
    }
}

void Menu::read_score_file(int top5[5])
{
    std::ifstream fichier;
    fichier.open("autres/score", ios::in);
    string line;
    while(getline(fichier, line))
    {
        int number = atoi(line.c_str());
        ordonnerScore_Top5(number, top5);
    }
    fichier.close();
}

//on a besoin cette fonction car le compilateur ne connaitre pas la vrai funtion to_string de STD
string Menu:: to_string(int number)
{
    stringstream ss;
    ss << number;
    string str;
    ss >> str;

    return str;
}

void Menu::affichageScore()
{
    SDL_SetRenderDrawColor(pRenderer, 60, 60, 60, 255);
    SDL_RenderClear(pRenderer);
    int top5[5] = {0};
    read_score_file(top5);
    sort(top5, top5 + 5);
    int PosY = 0;
    for(int i = 0; i < 5 ; ++i)
    {
        int PosX = 0;
        string number_string = to_string(top5[4-i]);
        int j = 0;
        while(number_string[j] != '\0')
        {
            afficherChiffre(numberTexture, number_string[j], 120, PosX, PosY);
            PosX += 100;
            ++j;
        }
        PosY += 130;
    }
    SDL_RenderPresent(pRenderer);
}

void Menu::setScore(int new_Score)
{
    ofstream scoreFile("autres/score", ios::in | ios:: app);
    scoreFile<<new_Score;
    scoreFile<<'\n';
    cout<<"Score Finale: "<< new_Score<< endl;
    scoreFile.close();
}
