#include "Joueur.hpp"
#include <string>
//std::fstream playerfile;

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
    cout << "Please!!! Enter a player Name " << endl;
    cin >> newName ;
    playerFile<<newName + ": 0" + '\n';
    playerFile.close();
    playerName = newName;
}
void Joueur::gestion_score(int new_Score)
{
    int min_score = tab_score[0];
    int pos = 0 ;
    for(int i = 0; i < 5; ++i)
    {
        if(tab_score[i] <= min_score)
        {
            pos = i;
        }
    }
    if(tab_score[pos] <= new_Score)
    {
        tab_score[pos] = new_Score;
    }
}

void Joueur::getScore()
{
    string score_line;
    if(playerFile)
    {
        while(getline(playerFile,score_line))
        {
            int value = atoi(score_line.c_str());
            gestion_score(value);
        }
        //playerFile.close();
    }
    sort(tab_score, tab_score +5);
    for(int i = 4; i >= 0 ; --i)
    {
        cout<< tab_score[i] <<endl;
    }
}

void Joueur::setScore( int newScore)
{
    playerFile<<newScore +'\n';
    cout<<"Score Finale "<< newScore<< endl;
    playerFile.close();
    playerScore = newScore;
}
