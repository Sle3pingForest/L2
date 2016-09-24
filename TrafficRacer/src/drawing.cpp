//
//  drawing.cpp
//  SDL2
//
//  Created by Arnaud on 24/09/2016.
//  Copyright © 2016 Arnaud. All rights reserved.
//

#include "drawing.hpp"
#include <math.h>

void drawTriangle()
{
    SDL_Point triangle[4];
    triangle[0].x = triangle[0].y = 200;
    triangle[1].x = 400;
    triangle[1].y = 200;
    triangle[2].x = 300;
    triangle[2].y = 100;
    triangle[3].x = triangle[3].y = triangle[0].x;
    
    SDL_SetRenderDrawColor(pRenderer, 255, 0, 0, 255);
    SDL_RenderDrawLines(pRenderer, triangle, 4);
}

void drawEchiquier()
{
    SDL_Rect echiquier[32];
    int pos_x = 0;
    int pos_y = 0;
    
    for (int i=0; i<8; ++i)
    {
        for (int j=0; j<4; ++j)
        {
            echiquier[j+i*4].x = pos_x + j*(SCREEN_WIDTH/4);
            echiquier[j+i*4].y = pos_y;
            echiquier[j+i*4].w = SCREEN_WIDTH/8;
            echiquier[j+i*4].h = SCREEN_HEIGHT/8;
        }

        pos_x = (pos_x == 0) ? SCREEN_WIDTH/8 :0;
        pos_y += SCREEN_HEIGHT/8;
    }
    
    SDL_RenderFillRects(pRenderer, echiquier, 32);
    SDL_SetRenderDrawColor(pRenderer, 255, 0, 0, 255);
    //SDL_RenderDrawRects(pRenderer, echiquier, 32);
}
