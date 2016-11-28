//
//  main.cpp
//  SDL2
//
//  Created by Arnaud on 24/09/Ķ2016.
//  Copyright © 2016 Arnaud. All rights reserved.
//

#include "Menu.hpp"

int main(int argc, const char * argv[])
{
<<<<<<< HEAD
    Menu menu;
    if (!menu.InitSDL())
        return -1;
    else
        menu.boucle();
=======

    Joueur joueur;
    cout<<joueur.getScore()<<endl;

    Partie partie;
    partie.play();
    joueur.setScore(partie.play());
>>>>>>> c5892eaf1bdbc6875d694b1b708f13f732d54f52
    return 0;
}
