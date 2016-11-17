#include "Joueur.hpp"

std::fstream playerfile;

fstream playerFile("autres/Player", ios::in | ios::out  | ios::app);


Joueur::Joueur()
{
    string defaultName = "Computer";
    playerName = defaultName;
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
    //std::ofstream playerFile;
    //playerFile.open("autres/Player");
    playerFile<<newName + ": 0" + '\n';
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
