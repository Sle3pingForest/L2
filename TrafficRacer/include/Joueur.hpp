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
<<<<<<< HEAD
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
    int tab_score[5] = {0};
=======
    public:
        Joueur();
        Joueur(string nname);

        int getScore();
        void setScore(int newScore);
        string getName();
        void setName();
        void gestion_score(int newscore);
    protected:
    private:
        string playerName;
        int playerScore;
        int tab_score[5] = {};
>>>>>>> c5892eaf1bdbc6875d694b1b708f13f732d54f52
};

#endif /* Joueur_hpp */
