#ifndef Decor_gestionnaire_hpp
#define Decor_gestionnaire_hpp

#include <stdio.h>
#include "Decor.hpp"

class Decor_gestionnaire {
public:
    Decor_gestionnaire();
    ~Decor_gestionnaire();
    
    void gestion(int vitesse);
    void afficherDecors(SDL_Texture* decorTexture);
    
private:
    static const int nb_decors = 30;
    Decor* tabDecors[nb_decors];
};

#endif /* Decor_gestionnaire_hpp */
