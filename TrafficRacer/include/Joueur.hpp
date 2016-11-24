#ifndef Joueur_hpp
#define Joueur_hpp
#include <fstream>
#include <iostream>

using namespace std;

class Joueur
{
    public:
        Joueur();
        Joueur(string nname);
    
        int getScore();
        void setScore(int newScore);
        string getName();
        void setName();
    protected:
    private:
        string playerName;
        int playerScore = 0;
};


#endif /* Joueur_hpp */
