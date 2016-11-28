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
    //joueur.getScore();

    Partie partie;
    cout<<"yolo--------:" << partie.play()<<endl;
    joueur.setScore(partie.play());
    return 0;
}
