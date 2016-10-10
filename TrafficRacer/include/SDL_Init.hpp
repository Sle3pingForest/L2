//
//  SDL_Init.hpp
//  SDL2
//
//  Created by Arnaud on 24/09/2016.
//  Copyright © 2016 Arnaud. All rights reserved.
//

#ifndef SDL_Init_hpp
#define SDL_Init_hpp

#include "Header.hpp"

bool InitSDLEverything();
bool InitSDL();

bool CreateWindow();
bool CreateRenderer();
bool CreateWindowAndRenderer();

SDL_Texture* LoadBmpWithTransparency(char* emplacement, Uint8 redTransparency, Uint8 greenTransparency, Uint8 blueTransparency);

#endif /* SDL_Init_hpp */
