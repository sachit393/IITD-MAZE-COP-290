#include "helper.h"
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





TTF_Font* font;

void disptext(SDL_Renderer* gRenderer, int x, int y, int w, int h, char* s,int r,int g,int b){
    //writing text in the box


    TTF_Init();
                //this opens a font style and sets a size
    
    TTF_Font* Sans = TTF_OpenFont("Lato-Black.ttf", 30);          //CHANGE THE FONT PATH TO AN APPROPRIATE ONE ACCORDING TO YOUR SYSTEM

    // this is the color in rgb format,
    // maxing out all would give you the color white,
    // and it will be your text's color
    SDL_Color White = {static_cast<Uint8>(r), static_cast<Uint8>(g), static_cast<Uint8>(b)};

    // as TTF_RenderText_Solid could only be used on
    // SDL_Surface then you have to create the surface first
    SDL_Surface* surfaceMessage = TTF_RenderText_Solid(Sans, s, White);

    // now you can convert it into a texture
    SDL_Texture* Message = SDL_CreateTextureFromSurface(gRenderer, surfaceMessage);

    SDL_Rect Message_rect; //create a rect
    Message_rect.x = x;  //controls the rect's x coordinate
    Message_rect.y = y; // controls the rect's y coordinte
    Message_rect.w = w; // controls the width of the rect
    Message_rect.h = h; // controls the height of the rect

    // (0,0) is on the top left of the window/screen,
    // think a rect as the text's box,
    // that way it would be very simple to understand

    // Now since it's a texture, you have to put RenderCopy
    // in your game loop area, the area where the whole code executes

    // you put the renderer's name first, the Message,
    // the crop size (you can ignore this if you don't want
    // to dabble with cropping), and the rect which is the size
    // and coordinate of your texture
    SDL_RenderCopy(gRenderer, Message, NULL, &Message_rect);

    // Don't forget to free your surface and texture
    SDL_FreeSurface(surfaceMessage);
    SDL_DestroyTexture(Message);
                TTF_CloseFont(Sans);
                TTF_Quit();


}


void playaudio(Mix_Music *m){
    // Inilialize SDL_mixer , exit if fail
    //if( SDL_Init(SDL_INIT_AUDIO) < 0 ) exit(1);
    // Setup audio mode
    //Mix_OpenAudio(22050,AUDIO_S16SYS,2,640);
    //Mix_Music *mus , *mus2 ;  // Background Music
    //Mix_Chunk *wav , *wav2 ;  // For Sounds
    //mus = Mix_LoadMUS(s);
    //mus2 = Mix_LoadMUS("./mixer/aria.mp3");
    //wav = Mix_LoadWAV("./mixer/po_p2k.wav");
    //wav2 = Mix_LoadWAV("./mixer/start.wav");
    Mix_PlayMusic(m,0); //Music loop=1
    //Mix_PlayChannel(-1,wav,0);
    //Mix_PlayChannel(-1,mus,0);
}


