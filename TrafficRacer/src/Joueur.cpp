#include "Joueur.hpp"
#include <string>
//std::fstream playerfile;

fstream playerFile("autres/score", ios::in | ios::out  | ios::app);


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
    cout << "Please!!! Enter a player Name " << endl;
    cin >> newName ;
    playerFile<<newName + ": 0" + '\n';
    playerFile.close();
    playerName = newName;
}


void Joueur::setScore( int new_Score)
{
    playerFile<<new_Score;
    playerFile<<'\n';
    cout<<"Score Finale: "<< new_Score<< endl;
    playerFile.close();
}
