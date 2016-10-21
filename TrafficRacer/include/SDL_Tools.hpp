//
//  SDL_Init.hpp
//  SDL2
//
//  Created by Arnaud on 24/09/2016.
//  Copyright © 2016 Arnaud. All rights reserved.
//

#ifndef SDL_Init_hpp
#define SDL_Init_hpp

#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <SDL2/SDL.h>

//Variables globlales taille de la fenêtre
extern int SCREEN_WIDTH;
extern int SCREEN_HEIGHT;
extern int SCREEN_FPS;

//Variables globales pour rendu SDL
extern SDL_Window *pWindow;
extern SDL_Renderer *pRenderer;

//Fonction liées à SDL
bool InitSDLEverything();
bool InitSDL();
bool CreateWindow();
bool CreateRenderer();
bool CreateWindowAndRenderer();

SDL_Texture* LoadBmpWithTransparency(const char* emplacement, Uint8 redTransparency, Uint8 greenTransparency, Uint8 blueTransparency);

#endif /* SDL_Init_hpp */
