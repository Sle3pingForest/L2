#include "Joueur.hpp"



Joueur::Joueur()
{
    string nameDefault = "Computer";
    playerName = nameDefault;
}

Joueur::Joueur(string name)
{
    playerName = name;
}

string Joueur::getName()
{
    return playerName;
}

void Joueur::setName()
{
    string newName;
    string line;
    cout << "Please!!! Enter a player Name " << endl;
    cin >> newName ;
    std::ofstream playerFile;
    playerFile.open("autres/Player");
    if (newName == "")
    {
        newName= "Computer";
        playerFile<<newName + ": "<< getScore();
    }
    else
    {
        playerFile<<newName;
    }
    playerFile.close();
    playerName = newName;
}

int Joueur::getScore()
{
    return playerScore;
}

void Joueur::setScore( int newScore)
{
    playerScore = newScore;
}

Joueur::~Joueur()
{
    //dtor
}
