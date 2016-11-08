//
//  Decor_gestionnaire.hpp
//  TrafficRacer
//
//  Created by Arnaud on 08/11/2016.
//  Copyright © 2016 Arnaud. All rights reserved.
//

#ifndef Decor_gestionnaire_hpp
#define Decor_gestionnaire_hpp

#include <stdio.h>
#include "Decor.hpp"

class Decor_gestionnaire {
public:
    Decor_gestionnaire();
    virtual ~Decor_gestionnaire();
    
    void gestion(int vitesse);
    void afficherDecors(SDL_Texture* decorTexture);
    
private:
    static const int nb_decors = 30;
    Decor* tabDecors[nb_decors];
};

#endif /* Decor_gestionnaire_hpp */
