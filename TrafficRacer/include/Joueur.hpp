#ifndef Joueur_hpp
#define Joueur_hpp

#include <fstream>
#include <iostream>
#include <algorithm>
#include <list>
#include <string>

using namespace std;

class Joueur
{
public:
    Joueur();
    Joueur(string nname);
    void setScore(int newScore);
    string getName();
    void setName();

protected:
private:
    string playerName;
    int playerScore;
};

#endif /* Joueur_hpp */
