//
//  drawing.cpp
//  SDL2
//
//  Created by Arnaud on 24/09/2016.
//  Copyright © 2016 Arnaud. All rights reserved.
//

#include "drawing.hpp"
#include <math.h>
#include "Decor.hpp"
#include "Voiture.h"

void CreateRoad()
{
    SDL_Rect road;
    road.w = SCREEN_WIDTH*0.7;
    road.h = SCREEN_HEIGHT;
    road.x = (SCREEN_WIDTH - road.w)/2;
    road.y = 0;
    SDL_RenderFillRect(pRenderer, &road);
    SDL_SetRenderDrawColor(pRenderer, 0, 0, 255, 255);
}


void drawGame()
{

    CreateRoad();

    Decor decor;

    decor.CreateDecor();

    Voiture voiture;
    voiture.CreateCar();

}
