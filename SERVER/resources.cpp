
#include "resources.h"
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



using namespace std;
//Current displayed texture

int oldC = 0;



int manhattanDistance(pair<int,int>pr1,pair<int,int>pr2){
        return abs(pr1.first-pr2.first)+abs(pr2.second-pr1.second);
}


pair<int,int> generateRandomPoint(int m){
        srand(time(0)+m);

        int x = rand()%1000;
        int y = rand()%1000;

        return {x,y};
}

bool delay(){
        int temp = generateRandomPoint(0).first;
        if(temp!=oldC) {
                oldC = temp;
                return true;
        }
        else return false;
}



SDL_Texture* loadFromFile( std::string path )
{
 
        //The final texture

        //Load image at specified path
        SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
        if( loadedSurface == NULL )
        {
                printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
        }
        else
        {
                //Color key image

                //Create texture from surface pixels
        imageTexture = SDL_CreateTextureFromSurface( gRenderer, loadedSurface );
                if( imageTexture == NULL )
                {
                        printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
                }
                else
                {
                        
                }

                //Get rid of old loaded surface
                SDL_FreeSurface( loadedSurface );
        }

        //Return success

        return imageTexture;
}
