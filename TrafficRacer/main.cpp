//
//  main.cpp
//  SDL2
//
//  Created by Arnaud on 24/09/Ķ2016.
//  Copyright © 2016 Arnaud. All rights reserved.
//

#include "Partie.hpp"
#include "Joueur.hpp"

int main(int argc, const char * argv[])
{

    Joueur joueur;
    cout<<joueur.getScore()<<endl;

    Partie partie;
    partie.play();
    joueur.setScore(partie.play());
    return 0;
}
