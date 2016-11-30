#ifndef SDL_Init_hpp
#define SDL_Init_hpp

#include "Constantes.hpp"

bool InitSDL();
SDL_Texture* LoadBmpWithTransparency(const char* emplacement, Uint8 redTransparency, Uint8 greenTransparency, Uint8 blueTransparency);

#endif /* SDL_Init_hpp */
