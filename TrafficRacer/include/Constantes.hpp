#ifndef Constantes_hpp
#define Constantes_hpp

#include <stdlib.h>
#include <SDL2/SDL.h>

extern SDL_Window *pWindow;
extern SDL_Renderer *pRenderer;

extern int SCREEN_WIDTH;
extern int SCREEN_HEIGHT;
extern int SCREEN_FPS;

extern const int LEVEL_WIDTH;
extern const int LEVEL_HEIGHT;

extern SDL_Rect camera;
extern float echelle;

#endif /* Constantes_hpp */
