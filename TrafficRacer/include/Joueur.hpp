#ifndef JOUEUR_H
#define JOUEUR_H

#include <fstream>
#include <iostream>
#include <string>
#include <stdio.h>

using namespace std;

class Joueur
{
    public:
        Joueur();
        Joueur(string nname);
        virtual ~Joueur();
        int getScore();
        void setScore(int newScore);
        string getName();
        void setName();
    protected:
    private:
        string playerName;
        int playerScore ;
};


#endif // JOUEUR_H
