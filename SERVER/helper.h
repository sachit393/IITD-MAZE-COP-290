#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <fcntl.h>
#include <arpa/inet.h>

#include <stdio.h>
#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <time.h>




#ifndef DISPTEXT // include guard
#define DISPTEXT

extern Mix_Music *musenter, *musclick, *musmusic ;



void disptext(SDL_Renderer* gRenderer, int x, int y, int w, int h, char* s,int r,int g,int b);

void playaudio(Mix_Music *m) ;


#endif 
