#pragma once

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <SDL2_ttf/SDL_ttf.h>
#include <SDL2_mixer/SDL_mixer.h>
#include <SDL2_net/SDL_net.h>
using namespace std;
//Current displayed texture

#ifndef RESOURCES // include guard
#define RESOURCES
//int oldC = 0;


extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;

extern SDL_Texture* gTexture ;


extern SDL_Texture* imageTexture ;

extern SDL_Window* gWindow ;

extern SDL_Renderer* gRenderer ;




int manhattanDistance(pair<int,int>pr1,pair<int,int>pr2);


pair<int,int> generateRandomPoint(int m);

bool delay();

enum KeyPress
{
    KEY_PRESS_UP,
    KEY_PRESS_DOWN,
    KEY_PRESS_LEFT,
    KEY_PRESS_RIGHT,
};


SDL_Texture* loadFromFile( std::string path );


#endif
