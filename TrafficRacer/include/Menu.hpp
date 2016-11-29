#ifndef Menu_hpp
#define Menu_hpp

#include "Partie.hpp"
#include "Joueur.hpp"
#include "Constantes.hpp"


class Menu
{
public:
    Menu();
    ~Menu();
    bool InitSDL();
    void boucle();
protected:
private:
    bool quit;
    int choix;

    SDL_Texture* logoTexture;
    SDL_Texture* scoreTexture;
    Joueur player;

    void gestion_touches();
    void affichage();
    void execute();
    void affichageScore();

    SDL_Texture* LoadBmpWithTransparency(const char* emplacement, Uint8 redTransparency, Uint8 greenTransparency, Uint8 blueTransparency);
    void chargementsImages();
    void afficherChiffre(char chiffre, int HauteurPolice, int PosX, int PosY);

    void afficherNombre(int nombre, int HauteurPolice, int PosX, int PosY);

};

#endif /* Menu_hpp */
