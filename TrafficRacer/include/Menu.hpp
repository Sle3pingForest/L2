#ifndef Menu_hpp
#define Menu_hpp

#include "Constantes.hpp"
#include "Partie.hpp"

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
    
    void gestion_touches();
    void affichage();
    void execute();
};

#endif /* Menu_hpp */
