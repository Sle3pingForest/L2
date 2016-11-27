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
    Menu menu;
    if (!menu.InitSDL())
        return -1;
    else
        menu.boucle();
    return 0;
    
}
