#ifndef SDL_Init_hpp
#define SDL_Init_hpp

#include "Constantes.hpp"

bool InitSDL();
SDL_Texture* LoadBmpWithTransparency(const char* emplacement, Uint8 redTransparency, Uint8 greenTransparency, Uint8 blueTransparency);
void afficherChiffre(SDL_Texture* texture, char chiffre, int HauteurPolice, int PosX, int PosY);
void afficherNombre(SDL_Texture* texture, int nombre, int HauteurPolice, int PosX, int PosY);
#endif /* SDL_Init_hpp */
