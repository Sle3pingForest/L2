#ifndef Menu_hpp
#define Menu_hpp

#include <stdio.h>
#include <iostream>
#include "Partie.hpp"
#include "Constantes.hpp"
#include "SDL_Tools.hpp"
#include <algorithm>
#include <sstream>


class Menu
{
public:
    Menu();
    ~Menu();
    bool Init();
    void boucle();
protected:
private:
    bool quit;
    int choix;
    int top5[5] = {0};

    SDL_Texture* logoTexture;
    SDL_Texture* numberTexture;
    SDL_Texture* playTexture;
    SDL_Texture* hscoreTexture;
    SDL_Texture* exitTexture;

    string to_string( int number);
    void read_score_file();
    void ordonnerScore_Top5( int New_score);
    void gestion_touches();
    void affichage();
    void execute();
    void affichageScore();
    void chargementsImages();
    void setScore(int new_Score);
};

#endif /* Menu_hpp */
