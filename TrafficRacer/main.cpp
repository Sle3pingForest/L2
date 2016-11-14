//
//  main.cpp
//  SDL2
//
//  Created by Arnaud on 24/09/Ķ2016.
//  Copyright © 2016 Arnaud. All rights reserved.
//

#include "Partie.hpp"

int main(int argc, const char * argv[])
{
    Partie partie;
    partie.play();
    partie.~Partie();
    return 0;
}
