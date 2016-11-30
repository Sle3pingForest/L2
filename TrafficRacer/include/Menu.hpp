#ifndef Menu_hpp
#define Menu_hpp

#include "Partie.hpp"
#include "Joueur.hpp"
#include "Constantes.hpp"
#include "SDL_Tools.hpp"


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
    
    SDL_Texture* logoTexture;
    SDL_Texture* UITexture;
    SDL_Texture* scoreTexture;
    SDL_Texture* playTexture;
    SDL_Texture* hscoreTexture;
    SDL_Texture* exitTexture;
    
    
    void gestion_touches();
    void affichage();
    void execute();
    void affichageScore();
    

    void chargementsImages();
    void afficherChiffre(char chiffre, int HauteurPolice, int PosX, int PosY);
    
    void afficherNombre(int nombre, int HauteurPolice, int PosX, int PosY);

};

#endif /* Menu_hpp */
