#ifndef Joueur_hpp
#define Joueur_hpp
#include <fstream>
#include <iostream>
#include <algorithm>
#include <list>

using namespace std;

class Joueur
{
    public:
        Joueur();
        Joueur(string nname);

        void getScore();
        void setScore(int newScore);
        string getName();
        void setName();
        void gestion_score(int newscore);
    protected:
    private:
        string playerName;
        int playerScore;
        int tab_score[5] = {};
};


#endif /* Joueur_hpp */
