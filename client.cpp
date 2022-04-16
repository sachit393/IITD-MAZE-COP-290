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
#define MAX 37
#define PORT 8080
#define SA struct sockaddr

#include <stdio.h>
#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <time.h>
using namespace std;
const int HOSPITAL_BILL = 30;
const int SCREEN_WIDTH = 1520;
const int SCREEN_HEIGHT = 1020;
const int PLAYER_RADIUS = 10;
int temp = 0;
int lastx=0;
int lasty=0;
int k=0;
int oldC = 0;
int tempClip = 0;
int newC = 0;
SDL_Window* gWindow = NULL;
Uint32 start = 0;
bool running = false;
bool notScolded = true;
bool hungry = true;
bool insufficientMoney = false;
int temp2Clip = 450;
int temp3Clip = 500;
int temp4Clip = 500;
int temp5Clip = 500;
int temp6Clip = 500;
int temp7Clip = 500;
int temp8Clip = 500;
int temp9Clip = 500;
int temp10Clip = 500;

SDL_Renderer* gRenderer = NULL;

//Current displayed texture


   


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

SDL_Texture* gTexture = NULL;
enum KeyPress
{
    KEY_PRESS_UP,
    KEY_PRESS_DOWN,
    KEY_PRESS_LEFT,
    KEY_PRESS_RIGHT,
};

SDL_Texture* imageTexture = NULL;

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

TTF_Font* font;

void disptext(SDL_Renderer* gRenderer, int x, int y, int w, int h, char* s,int r,int g,int b){
    //writing text in the box


    TTF_Init();
                //this opens a font style and sets a size
    
    TTF_Font* Sans = TTF_OpenFont("Lato-Black.ttf", 30);          //CHANGE THE FONT PATH TO AN APPROPRIATE ONE ACCORDING TO YOUR SYSTEM

    // this is the color in rgb format,
    // maxing out all would give you the color white,
    // and it will be your text's color
    SDL_Color White = {r, g, b};

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


void playaudio(char* s){
    // Inilialize SDL_mixer , exit if fail
    if( SDL_Init(SDL_INIT_AUDIO) < 0 ) exit(1);
    // Setup audio mode
    Mix_OpenAudio(22050,AUDIO_S16SYS,2,640);
    Mix_Music *mus , *mus2 ;  // Background Music
    Mix_Chunk *wav , *wav2 ;  // For Sounds
    mus = Mix_LoadMUS(s);
    //mus2 = Mix_LoadMUS("./mixer/aria.mp3");
    //wav = Mix_LoadWAV("./mixer/po_p2k.wav");
    //wav2 = Mix_LoadWAV("./mixer/start.wav");
    Mix_PlayMusic(mus,0); //Music loop=1
    //Mix_PlayChannel(-1,wav,0);
    //Mix_PlayChannel(-1,mus,0);
}






class Player{

        public:
                SDL_Texture* colorTexFront = NULL;
                SDL_Texture* colorTexBack = NULL;
                SDL_Texture* colorTexLeft = NULL;
                SDL_Texture* colorTexRight = NULL;
                SDL_Texture* colorTexLeft2 = NULL;
                int x;
                int y;
                int speed = 7;
                int health;
                int energy;
                int happiness;
                int money;
                int knowledge;
                bool hasCycle;
                bool inMain = true;
                bool enterHostel = false;
                bool inLargeGround = false;
                bool inTennisCourt = false;
                bool inVolleyCourt = false;
                bool inLHC = false;
                bool inLHC108 = false;
                bool inLHC114 = false;
                bool inLHC325 = false;
                bool enterSAC = false;
                bool enterRestaurant = false;
                bool enterMasalaMix = false ;
                bool enterRajdhani = false ;
                bool enterChaayos = false ;
                bool enterShiru = false ;
                bool enterAmul = false ;
                bool enterNescafe = false ;
                bool enterCCD = false ;
                bool enterStaffCanteen = false ;
                bool enterDilli16 = false ;
                bool enterLibrary = false ;
                bool takenYulu = false;
                bool isSleeping = false;
                bool bankrupt = false;
                bool isStudying = false;
                int lastStepDirection = 0;

        Player(int xP,int yP,string colorP){
                health = 50;
                energy = 100;
                happiness = 50;
                money = 50;
                knowledge = 10;
                hasCycle = false;
                x = xP;
                y = yP;
                colorTexRight = loadFromFile(colorP+"-char-right.png");
                colorTexFront = loadFromFile(colorP+"-char-front.png");
                colorTexBack = loadFromFile(colorP+"-char-back.png");
                colorTexLeft = loadFromFile(colorP+"-char-left.png");
                colorTexLeft2 = loadFromFile(colorP+"-char-left.png");
        }


        void buyCycleIfPossible(){
                if(money>80 && !hasCycle){
                        money-=80;
                        speed +=1;
                        hasCycle = true;

                }
                
        }

        void hospitalize(){
                if(money<HOSPITAL_BILL){
                        // player loses
                }
                money-=HOSPITAL_BILL;
                energy = 100;
                health = 100;
                happiness = 50;
                x = 260;
                y = 550;
                inMain = true;
                enterHostel = false;
                inTennisCourt = false;
                inLargeGround = false;

        }

        void changeEnergy(int amount){
                energy+=amount;
                if(energy<0){
                        hospitalize();
                }
        }

        void changeHealth(int amount){
                health+=amount;
                if(health<0){
                        hospitalize();
                }
        }

        void changeHappiness(int amount){
                happiness+=amount;

                if(happiness<0){                // permanent decrease in energy due to lack of happiness
                        energy/=2;
                        happiness = 0;
                }

        }

        void changeKnowledge(int amount){
                knowledge+=amount;
        }
        void updateSpeed(){
                speed +=energy/10;
        }

        void move(int keyPress){

                

                        if(inMain){
                                if(keyPress == KEY_PRESS_UP){
                                        if(x>=870 && x<=890 && y-speed>=140 && y<=215){
                                                y-=speed+energy/40;
                                        }
                                        if(x>=520 && x<=540 && y-speed>=140 && y<=215){
                                                y-=speed+energy/40;
                                        }
                                        if(x>=330 && x<=350 && y-speed>=140 && y<=215){
                                                y-=speed+energy/40;
                                        }
                                        if(x>=120 && x<=145 && y-speed>=140 && y<=215){
                                                y-=speed+energy/40;
                                        }
                                        if(y+speed<=190 && y-speed>=160 && x<=1000 && x>=0){
                                                y-=speed+energy/40;                                        
                                        }
                                        if(x<=255 && x>=230 && y-speed>=165){
                                                y-=speed+energy/40;
                                        }
                                        if(x<=995 && x>=970 && y-speed>=750){
                                                y-=speed+energy/40;
                                        }
                                        if(x<=672 && x>=660 && y-speed>=312){
                                                y-=speed+energy/40;
                                        }
                                        if(x<=600 && x>=575 && y-speed>=547 && y<720){
                                                y-=speed+energy/40;
                                        }

                                        if(x<=800 && x>=760 && y-speed>=172 && y<600){
                                                y-=speed+energy/40;
                                        }
                                        if(x>=355 && x<=380 && y-speed>=302){
                                                y-=speed+energy/40;
                                        }

                                        if(x>=455 && x<=480 && y-speed>=302){
                                                y-=speed+energy/40;
                                        }
                                        // to enter shiru cafe
                                        if(x>=565 && x<=585 && y-speed>=750){
                                                y-=speed+energy/40;
                                        }
                                        // to enter amul
                                        if(x>=700 && x<=715 && y-speed>=750){
                                                y-=speed+energy/40;
                                        }
                                        // to enter nesacfe
                                        if(x>=850 && x<=865 && y-speed>=750){
                                                y-=speed+energy/40;
                                        }

                                }
                                if(keyPress == KEY_PRESS_DOWN){
                                        if(x>=870 && x<=890 && y+speed<=200){
                                                y+=speed+energy/40;
                                        }
                                        if(x>=520 && x<=540 && y+speed<=200){
                                                y+=speed+energy/40;
                                        }
                                        if(x>=330 && x<=350 && y+speed<=170){
                                                y+=speed+energy/40;
                                        }
                                        if(x>=120 && x<=145 && y+speed<=170){
                                                y+=speed+energy/40;
                                        }
                                        if(y+speed<=190 && x<=1000 && x>=0){
                                                y+=speed+energy/40;
                                        }
                                        if(x<=255 && x>=230 && y+speed<=990){
                                                y+=speed+energy/40;
                                        }
                                        if(x<=995 && x>=970 && y+speed<=990){
                                                y+=speed+energy/40;
                                        }

                                        if(x<=672 && x>=660 && y+speed<=557){
                                                y+=speed+energy/40;
                                        } 

                                        if(x<=600 && x>=575 && y+speed<=690 && y>=500){
                                                y+=speed+energy/40;
                                        }
                                        if(x<=800 && x>=760 && y+speed<=470 ){
                                                y+=speed+energy/40;
                                        }
                                        if(x>=355 && x<=380 && y+speed<=350 && y>=250){
                                                y+=speed+energy/40;
                                        }

                                        if(x>=455 && x<=480 && y+speed<=350 && y>=250){
                                                y+=speed+energy/40;
                                        }
                                        if(x>=565 && x<=585 && y+speed<=780 && y>700){
                                                y+=speed+energy/40;
                                        }

                                        if(x>=700 && x<=715 && y+speed<=780){
                                                y+=speed+energy/40;
                                        }
                                        if(x>=850 && x<=865 && y+speed<=780){
                                                y+=speed+energy/40;
                                        }
                                }
                                if(keyPress == KEY_PRESS_LEFT){
                                        if(y>=335 && y<=350 &&  x-speed>=760){
                                                x-=speed+energy/40;
                                        }
                                        if(y>=160 && y<=190 &&  x-speed>=0){
                                                x-=speed+energy/40;
                                        }
                                        if(970<=y && y<=990 && x-speed>=230){
                                                x-=speed+energy/40;
                                        }
                                        if(y>=740 && y<=760 && x-speed>=230){
                                                x-=speed+energy/40;
                                        }
                                        if(y>=307 && y<=320 && x-speed>=130){
                                                x-=speed+energy/40;
                                        }
                                        if(y>=480 && y<=497 && x-speed>=225){
                                                x-=speed+energy/40;
                                        }

                                        if(y>=543 && y<=560 && x-speed>=575){
                                                x-=speed+energy/40;
                                        }

                                        if(y>=543 && y<=560 && x-speed>=130 && x<400){
                                                x-=speed+energy/40;
                                        }
                                        if(y>=785 && y<=800 && x-speed>=160 && x<400){
                                                x-=speed+energy/40;
                                        }
                                        if(y>=875 && y<=895 && x-speed>=160 && x<400){
                                                x-=speed+energy/40;
                                        }
                                        if(y>=835 && y<=850 && x-speed>=980 && x>700){
                                                x-=speed+energy/40;
                                        }

                                }
                                if(keyPress == KEY_PRESS_RIGHT){
                                        if(335<=y && y<=350 && x+speed<=820){
                                                x+=speed+energy/40;
                                        }
                                        if(160<=y && y<=190 && x+speed<=1000){
                                                x+=speed+energy/40;
                                        }
                                        if(970<=y && y<=990 && x+speed<=1000){
                                                x+=speed+energy/40;
                                        }
                                        if(y>=740 && y<=760 && x+speed<=995){
                                                x+=speed+energy/40;
                                        }
                                        if(y>=307 && y<=320 && x+speed<=787){
                                                x+=speed+energy/40;
                                        }
                                        if(y>=480 && y<=497 && x+speed<=672){
                                                x+=speed+energy/40;
                                        }
                                        if(y>=543 && y<=560 && x+speed<=672 && x>400){
                                                x+=speed+energy/40;
                                        }
                                        if(y>=543 && y<=560 && x+speed<=265){
                                                x+=speed+energy/40;
                                        }
                                        if(y>=785 && y<=800 && x+speed<=250 && x<400){
                                                x+=speed+energy/40;
                                        }
                                        if(y>=875 && y<=895 && x+speed<=250 && x<400){
                                                x+=speed+energy/40;
                                        }

                                        if(y>=835 && y<=850 && x+speed<=1040 && x>700){
                                                x+=speed+energy/40;
                                        }

                                }
                        }
                        else if(!inMain){
                                  if (keyPress ==KEY_PRESS_UP){
                                        if(y-speed>=0){
                                                y-=speed+energy/40;
                                        }
                                  }
                                  if(keyPress == KEY_PRESS_DOWN){
                                        if(y+speed<=SCREEN_HEIGHT){
                                                y+=speed+energy/40;
                                        }
                                  }
                                  if(keyPress == KEY_PRESS_RIGHT){
                                        if(x+speed<=SCREEN_WIDTH){
                                                x+=speed+energy/40;
                                        }
                                  }
                                  if(keyPress == KEY_PRESS_LEFT){
                                        if(x-speed>=0){
                                                x-=speed+energy/40;;
                                        }
                                  }   
                        }
                

        }

        void incrementMoney(){
                if(delay()){
                        temp++;
                        if(temp==15){
                           money=min(money+10,100);
                           temp = 0;
                        }
                        if(takenYulu){
                                
                                        money=max(money-1,0);
                                
                            }
                        if(insufficientMoney){
                                insufficientMoney = false;
                        }
                }

        }

        void enter(){
                // enter into shivalik building
                                // shivalik                                     zanskar                             vidyanchal                            satpura                                   girnar and udaigiri                      nilgiri                                  karakoram                                         aravali                                jwalamukhi                            kumaon   
                if (inMain && ((x>=455 && x<=480 && y<=350 && y>=330) || (x>=365 && x<=390 && y<=350 && y>=330) || (y>=340 && y<=365 && x>=800 && x<=820) || (x>=755 && x<=800 && 463<=y && y<=480) || (x<=610 && x>=585 && y>=580 && y<=680) || (x>=115 && x<=145 && y>=125 && y<=145) || (x>=324 && x<=355 && y>=125 && y<=145) ||(x>=515 && x<=545 && y<=145 && y>=125) || (x>=865 && x<=895 && y<=145 && y>=125) || (x>=865 && x<=895 && y>=165 && y<=215) )){
                        enterHostel = true;
                        lastx = x;
                        lasty = y;
                        x = 150;
                        y = 150;
                        inMain = false;
                        inLargeGround = false;
                        enterRestaurant = false;
                        enterSAC = false;
                        enterMasalaMix = false;
                        enterRajdhani = false;
                        enterChaayos = false;
                        enterShiru = false;
                        enterAmul = false;
                        enterNescafe = false;
                        enterCCD = false;
                        enterStaffCanteen = false;
                        enterDilli16 = false;
                        enterLibrary = false;
                        inLHC = false;
                        inLHC108 = false;
                        inLHC114 = false;
                        inLHC325 = false;
                        isSleeping = false;
                        takenYulu = false;
                        inVolleyCourt = false;
                        inTennisCourt = false;
                        inLargeGround = false;
                }
                // exit from shivalik building

                else if(enterHostel && x>=65 && x<=210 && y>=65 && y<=210){
                        inMain = true;
                        x = lastx;
                        y = lasty;
                        enterHostel = false;
                        inLargeGround = false;
                        enterRestaurant = false;
                        enterSAC = false;
                        enterMasalaMix = false;
                        enterRajdhani = false;
                        enterChaayos = false;
                        enterShiru = false;
                        enterAmul = false;
                        enterNescafe = false;
                        enterCCD = false;
                        enterStaffCanteen = false;
                        enterDilli16 = false;
                        enterLibrary = false;
                        inLHC = false;
                        inLHC108 = false;
                        inLHC114 = false;
                        inLHC325 = false;
                        isSleeping = false;
                        takenYulu = false;
                        inVolleyCourt = false;
                        inTennisCourt = false;
                        inLargeGround = false;
                }
                // play table tennis in Shivalik
                else if(enterHostel && x>=830 && x<=1000 && y>=100 && y<=200){
                        energy-=10;

                        temp2Clip = 0;
                        if(energy<=0){
                                hospitalize();
                        }
                        health = min(100,health+10);
                        happiness = min(100,happiness+10);
                }
                // eating mess food
                else if(enterHostel && x>=400 && x<=530 && y>=140 && y<=290){
                        energy=min(energy+20,100);
                        temp3Clip = 0;
                }

                // sleeping
                else if(enterHostel && x>=1280 && x<=1450){
                        isSleeping = true;
                        inMain = false;
                        enterHostel = false;
                        inLargeGround = false;
                        enterRestaurant = false;
                        enterSAC = false;
                        enterMasalaMix = false;
                        enterRajdhani = false;
                        enterChaayos = false;
                        enterShiru = false;
                        enterAmul = false;
                        enterNescafe = false;
                        enterCCD = false;
                        enterStaffCanteen = false;
                        enterDilli16 = false;
                        enterLibrary = false;
                        inLHC = false;
                        inLHC108 = false;
                        inLHC114 = false;
                        inLHC325 = false;
                        takenYulu = false;
                        inVolleyCourt = false;
                        inTennisCourt = false;
                        inLargeGround = false;
                        
                }
                else if(isSleeping){
                        isSleeping = false;
                        enterHostel = true;
                        x = 1300;
                        y = 200;

                        inMain = false;
                        inLargeGround = false;
                        enterRestaurant = false;
                        enterSAC = false;
                        enterMasalaMix = false;
                        enterRajdhani = false;
                        enterChaayos = false;
                        enterShiru = false;
                        enterAmul = false;
                        enterNescafe = false;
                        enterCCD = false;
                        enterStaffCanteen = false;
                        enterDilli16 = false;
                        enterLibrary = false;
                        inLHC = false;
                        inLHC108 = false;
                        inLHC114 = false;
                        inLHC325 = false;
                        takenYulu = false;
                        inVolleyCourt = false;
                        inTennisCourt = false;
                        inLargeGround = false;
                }

                // entering largeGround
                else if(inMain && x>=120 && x<=220 && y>=540 && y<=570){
                        inLargeGround = true;
                        inMain = false;
                        enterHostel = false;
                        x = 1300;
                        y = 500;
                }
                // exit large ground
                else if (inLargeGround && x>=1350 && x<=1490 && y<=520 && y>=450){
                        inLargeGround = false;
                        inMain = true;
                        enterHostel = false;
                        inTennisCourt = false;
                        enterHostel = false;
                        inLargeGround = false;
                        enterRestaurant = false;
                        enterSAC = false;
                        enterMasalaMix = false;
                        enterRajdhani = false;
                        enterChaayos = false;
                        enterShiru = false;
                        enterAmul = false;
                        enterNescafe = false;
                        enterCCD = false;
                        enterStaffCanteen = false;
                        enterDilli16 = false;
                        enterLibrary = false;
                        inLHC = false;
                        inLHC108 = false;
                        inLHC114 = false;
                        inLHC325 = false;
                        isSleeping = false;
                        takenYulu = false;
                        inVolleyCourt = false;
                        x = 220;
                        y = 550;
                }
                // play football
                else if(inLargeGround && x>=450 && x<=530 && y<=200 && y>=130){
                        energy-=10;
                        if(energy<=0){
                                hospitalize();
                        }
                        health = min(100,health+10);
                        happiness = min(100,happiness+10);
                        temp6Clip = 0;

                }
                // play cricket
                else if(inLargeGround && x>=300 && x<=400 && y<=680 && y>=460){
                        energy-=10;
                        if(energy<=0){
                                hospitalize();
                        }
                        health = min(100,health+10);
                        happiness = min(100,happiness+10);
                        temp7Clip = 0; 
                }

                // play hockey
                else if(inLargeGround && x>=450 && x<=530 && y<=920 && y>=780){
                        energy-=10;
                        if(energy<=0){
                                hospitalize();
                        }
                        health = min(100,health+10);
                        happiness = min(100,happiness+10);
                        temp8Clip = 0;
                }

                // entering tennis court
                else if(inMain && y>=300 && y<=315 && x>=350 && x<=370){
                        inTennisCourt = true;
                        inMain = false;
                        inLargeGround = false;
                        enterHostel = false;
                        x = 1300;
                        y = 500;
                        enterRestaurant = false;
                        enterSAC = false;
                        enterMasalaMix = false;
                        enterRajdhani = false;
                        enterChaayos = false;
                        enterShiru = false;
                        enterAmul = false;
                        enterNescafe = false;
                        enterCCD = false;
                        enterStaffCanteen = false;
                        enterDilli16 = false;
                        enterLibrary = false;
                        inLHC = false;
                        inLHC108 = false;
                        inLHC114 = false;
                        inLHC325 = false;
                        isSleeping = false;
                        takenYulu = false;
                        inVolleyCourt = false;
                        inLargeGround = false;
                        
                }

                // play tennis
                else if(inTennisCourt && y>=660 && y<=950 && x<=1200 && x>=1000){
                        energy-=10;
                        if(energy<=0){
                                hospitalize();
                        }
                        temp4Clip = 0;
                        health = min(100,health+10);
                        happiness = min(100,happiness+10);
                }
                // exit tennis court
                else if (inTennisCourt && x>=1350 && x<=1490 && y<=520 && y>=450){
                        inLargeGround = false;
                        inMain = true;
                        enterHostel = false;
                        inTennisCourt = false;
                        enterHostel = false;
                        enterRestaurant = false;
                        enterSAC = false;
                        enterMasalaMix = false;
                        enterRajdhani = false;
                        enterChaayos = false;
                        enterShiru = false;
                        enterAmul = false;
                        enterNescafe = false;
                        enterCCD = false;
                        enterStaffCanteen = false;
                        enterDilli16 = false;
                        enterLibrary = false;
                        inLHC = false;
                        inLHC108 = false;
                        inLHC114 = false;
                        inLHC325 = false;
                        isSleeping = false;
                        takenYulu = false;
                        inVolleyCourt = false;
                        inTennisCourt = false;
                        inLargeGround = false;
                        x = 370;
                        y = 320;
                }

                // enter volleyBall Court
                else if(inMain && y>=300 && y<=320 && x>=498 && x<=510){
                        inTennisCourt = false;
                        inVolleyCourt = true;
                        inLargeGround = false;
                        enterHostel = false;
                        inMain = false;
                        inMain = false;
                        enterHostel = false;
                        inLargeGround = false;
                        enterRestaurant = false;
                        enterSAC = false;
                        enterMasalaMix = false;
                        enterRajdhani = false;
                        enterChaayos = false;
                        enterShiru = false;
                        enterAmul = false;
                        enterNescafe = false;
                        enterCCD = false;
                        enterStaffCanteen = false;
                        enterDilli16 = false;
                        enterLibrary = false;
                        inLHC = false;
                        inLHC108 = false;
                        inLHC114 = false;
                        inLHC325 = false;
                        isSleeping = false;
                        takenYulu = false;
                        inTennisCourt = false;
                        inLargeGround = false;
                        x = 1300;
                        y = 500;
                }
                // playvolleyball
                else if(inVolleyCourt && x>=630 && x<=740 && y>=800 && y<=900 ){
                        energy-=10;
                        if(energy<=0){
                                hospitalize();
                        }
                        health = min(100,health+10);
                        happiness = min(100,happiness+10);
                        temp5Clip = 0;
                }

                // exit volley court
                else if (inVolleyCourt && x>=1350 && x<=1490 && y<=520 && y>=450){
                        inMain = true;
                        enterHostel = false;
                        inTennisCourt = false;
                        inVolleyCourt = false;
                        inMain = false;
                        enterHostel = false;
                        inLargeGround = false;
                        enterRestaurant = false;
                        enterSAC = false;
                        enterMasalaMix = false;
                        enterRajdhani = false;
                        enterChaayos = false;
                        enterShiru = false;
                        enterAmul = false;
                        enterNescafe = false;
                        enterCCD = false;
                        enterStaffCanteen = false;
                        enterDilli16 = false;
                        enterLibrary = false;
                        inLHC = false;
                        inLHC108 = false;
                        inLHC114 = false;
                        inLHC325 = false;
                        isSleeping = false;
                        takenYulu = false;
                        inTennisCourt = false;
                        inLargeGround = false;
                        x = 500;
                        y = 320;
                }

                // enter lhc
                else if(inMain && y>=870 && y<=890 && x>=140 && x<=220){
                        inLHC = true;
                        inLargeGround = false;
                        enterHostel = false;
                        inTennisCourt = false;
                        inVolleyCourt = false;
                        inMain = false;
                        inMain = false;
                        enterHostel = false;
                        inLargeGround = false;
                        enterRestaurant = false;
                        enterSAC = false;
                        enterMasalaMix = false;
                        enterRajdhani = false;
                        enterChaayos = false;
                        enterShiru = false;
                        enterAmul = false;
                        enterNescafe = false;
                        enterCCD = false;
                        enterStaffCanteen = false;
                        enterDilli16 = false;
                        enterLibrary = false;
                        inLHC108 = false;
                        inLHC114 = false;
                        inLHC325 = false;
                        isSleeping = false;
                        takenYulu = false;
                        inVolleyCourt = false;
                        inTennisCourt = false;
                        inLargeGround = false;
                        x = 1300;
                        y = 500;
                }

                // study in lh108(lamda calculas)

                else if(inLHC && y>=450 && y<=650 && x>=400 && x<=580){
                        inLHC108 = true;
                        inLHC = false;
                        inLargeGround = false;
                        enterHostel = false;
                        inTennisCourt = false;
                        inVolleyCourt = false;
                        inMain = false;
                        inMain = false;
                        enterHostel = false;
                        inLargeGround = false;
                        enterRestaurant = false;
                        enterSAC = false;
                        enterMasalaMix = false;
                        enterRajdhani = false;
                        enterChaayos = false;
                        enterShiru = false;
                        enterAmul = false;
                        enterNescafe = false;
                        enterCCD = false;
                        enterStaffCanteen = false;
                        enterDilli16 = false;
                        enterLibrary = false;
                        inLHC = false;
                        inLHC114 = false;
                        inLHC325 = false;
                        isSleeping = false;
                        takenYulu = false;
                        inVolleyCourt = false;
                        inTennisCourt = false;
                        inLargeGround = false;
                }
                // exit lhc108
                else if (inLHC108 && x>=1350 && x<=1490 && y<=520 && y>=450){
                        inLargeGround = false;
                        inMain = false;
                        enterHostel = false;
                        inTennisCourt = false;
                        inLHC = true;
                        inLHC108 = false;
                        inMain = false;
                        enterHostel = false;
                        inLargeGround = false;
                        enterRestaurant = false;
                        enterSAC = false;
                        enterMasalaMix = false;
                        enterRajdhani = false;
                        enterChaayos = false;
                        enterShiru = false;
                        enterAmul = false;
                        enterNescafe = false;
                        enterCCD = false;
                        enterStaffCanteen = false;
                        enterDilli16 = false;
                        enterLibrary = false;
                        inLHC108 = false;
                        inLHC114 = false;
                        inLHC325 = false;
                        isSleeping = false;
                        takenYulu = false;
                        inVolleyCourt = false;
                        inTennisCourt = false;
                        inLargeGround = false;
                        x = 500;
                        y = 500;
                }


                // study in lh114(arm)

                else if(inLHC && y>=450 && y<=650 && x>=680 && x<=860){
                        inLHC108 = false;
                        inLHC114 = true;
                        inLHC = false;
                        inLargeGround = false;
                        enterHostel = false;
                        inTennisCourt = false;
                        inVolleyCourt = false;
                        inMain = false;
                        inMain = false;
                        enterHostel = false;
                        inLargeGround = false;
                        enterRestaurant = false;
                        enterSAC = false;
                        enterMasalaMix = false;
                        enterRajdhani = false;
                        enterChaayos = false;
                        enterShiru = false;
                        enterAmul = false;
                        enterNescafe = false;
                        enterCCD = false;
                        enterStaffCanteen = false;
                        enterDilli16 = false;
                        enterLibrary = false;
                        inLHC = false;
                        inLHC108 = false;
                        inLHC325 = false;
                        isSleeping = false;
                        takenYulu = false;
                        inVolleyCourt = false;
                        inTennisCourt = false;
                        inLargeGround = false;
                }
                // exit lhc114
                else if (inLHC114 && x>=1350 && x<=1490 && y<=520 && y>=450){
                        inLargeGround = false;
                        inMain = false;
                        enterHostel = false;
                        inTennisCourt = false;
                        inLHC = true;
                        inLHC108 = false;
                        inLHC114 = false;
                        inMain = false;
                        enterHostel = false;
                        inLargeGround = false;
                        enterRestaurant = false;
                        enterSAC = false;
                        enterMasalaMix = false;
                        enterRajdhani = false;
                        enterChaayos = false;
                        enterShiru = false;
                        enterAmul = false;
                        enterNescafe = false;
                        enterCCD = false;
                        enterStaffCanteen = false;
                        enterDilli16 = false;
                        enterLibrary = false;
                        inLHC108 = false;
                        inLHC114 = false;
                        inLHC325 = false;
                        isSleeping = false;
                        takenYulu = false;
                        inVolleyCourt = false;
                        inTennisCourt = false;
                        inLargeGround = false;
                        x = 700;
                        y = 500;
                }


                // study in lh325(stats)

                else if(inLHC && y>=450 && y<=650 && x>=140 && x<=300){
                        inLHC108 = false;
                        inLHC114 = false;
                        inLHC325 = true;
                        inLHC = false;
                        inLargeGround = false;
                        enterHostel = false;
                        inTennisCourt = false;
                        inVolleyCourt = false;
                        inMain = false;
                        inMain = false;
                        enterHostel = false;
                        inLargeGround = false;
                        enterRestaurant = false;
                        enterSAC = false;
                        enterMasalaMix = false;
                        enterRajdhani = false;
                        enterChaayos = false;
                        enterShiru = false;
                        enterAmul = false;
                        enterNescafe = false;
                        enterCCD = false;
                        enterStaffCanteen = false;
                        enterDilli16 = false;
                        enterLibrary = false;
                        inLHC = false;
                        inLHC108 = false;
                        inLHC114 = false;
                        isSleeping = false;
                        takenYulu = false;
                        inVolleyCourt = false;
                        inTennisCourt = false;
                        inLargeGround = false;
                }
                // exit lhc325
                else if (inLHC325 && x>=1350 && x<=1490 && y<=520 && y>=450){
                        inLargeGround = false;
                        inMain = false;
                        enterHostel = false;
                        inTennisCourt = false;
                        inLHC = true;
                        inLHC108 = false;
                        inLHC114 = false;
                        inLHC325 = false;
                        inMain = false;
                        enterHostel = false;
                        inLargeGround = false;
                        enterRestaurant = false;
                        enterSAC = false;
                        enterMasalaMix = false;
                        enterRajdhani = false;
                        enterChaayos = false;
                        enterShiru = false;
                        enterAmul = false;
                        enterNescafe = false;
                        enterCCD = false;
                        enterStaffCanteen = false;
                        enterDilli16 = false;
                        enterLibrary = false;
                        inLHC108 = false;
                        inLHC114 = false;
                        inLHC325 = false;
                        isSleeping = false;
                        takenYulu = false;
                        inVolleyCourt = false;
                        inTennisCourt = false;
                        inLargeGround = false;
                        x = 300;
                        y = 500;
                }

                
                // exit lhc

                else if (inLHC && x>=1350 && x<=1490 && y<=520 && y>=450){
                        inLargeGround = false;
                        inMain = true;
                        enterHostel = false;
                        inTennisCourt = false;
                        inLHC108 = false;
                        inLHC= false;
                        enterHostel = false;
                        inLargeGround = false;
                        enterRestaurant = false;
                        enterSAC = false;
                        enterMasalaMix = false;
                        enterRajdhani = false;
                        enterChaayos = false;
                        enterShiru = false;
                        enterAmul = false;
                        enterNescafe = false;
                        enterCCD = false;
                        enterStaffCanteen = false;
                        enterDilli16 = false;
                        enterLibrary = false;
                        inLHC = false;
                        inLHC108 = false;
                        inLHC114 = false;
                        inLHC325 = false;
                        isSleeping = false;
                        takenYulu = false;
                        inVolleyCourt = false;
                        inTennisCourt = false;
                        inLargeGround = false;

                        x = 250;
                        y = 890;
                }
            // enter into restaurants
        
                else if (!enterRestaurant && (x>=(SCREEN_WIDTH / 22+120+130) && x<=(SCREEN_WIDTH / 22+150+130) && y<=(SCREEN_HEIGHT / 22+425 + (SCREEN_HEIGHT / 20)) && y>=(SCREEN_HEIGHT / 22+425) )                                                               //Masala Mix
                && inMain){
                        enterMasalaMix = true;
                        enterRestaurant = true;
                        inMain = false;
                        enterHostel = false;
                        inLargeGround = false;
                        enterSAC = false;
                        enterRajdhani = false;
                        enterChaayos = false;
                        enterShiru = false;
                        enterAmul = false;
                        enterNescafe = false;
                        enterCCD = false;
                        enterStaffCanteen = false;
                        enterDilli16 = false;
                        enterLibrary = false;
                        inLHC = false;
                        inLHC108 = false;
                        inLHC114 = false;
                        inLHC325 = false;
                        isSleeping = false;
                        takenYulu = false;
                        inVolleyCourt = false;
                        inTennisCourt = false;
                        inLargeGround = false;
                        x = SCREEN_WIDTH - 290;
                        y = 150;
                        inMain = false;
                        playaudio("/Users/eshan/Downloads/enter-sound.wav") ;
                }

                else if (
                (!enterRestaurant && x>=(SCREEN_WIDTH / 22+95+160+100) && x<=(SCREEN_WIDTH / 22+95+185+100) && y<=(SCREEN_HEIGHT / 22+425 + (SCREEN_HEIGHT / 20)) && y>=SCREEN_HEIGHT / 22+425    )       //Rajdhani
                && inMain){
                        enterRajdhani = true;
                        enterRestaurant = true;
                        inMain = false;
                        enterHostel = false;
                        inLargeGround = false;
                        enterSAC = false;
                        enterMasalaMix = false;
                        enterChaayos = false;
                        enterShiru = false;
                        enterAmul = false;
                        enterNescafe = false;
                        enterCCD = false;
                        enterStaffCanteen = false;
                        enterDilli16 = false;
                        enterLibrary = false;
                        inLHC = false;
                        inLHC108 = false;
                        inLHC114 = false;
                        inLHC325 = false;
                        isSleeping = false;
                        takenYulu = false;
                        inVolleyCourt = false;
                        inTennisCourt = false;
                        inLargeGround = false;
                        x = SCREEN_WIDTH - 290;
                        y = 150;
                        inMain = false;
                        playaudio("/Users/eshan/Downloads/enter-sound.wav") ;
                }

                else if (!enterRestaurant &&
                (x>= SCREEN_WIDTH / 22+95+255+100 && x<=( SCREEN_WIDTH / 22+95+285+100) && y<=(SCREEN_HEIGHT / 22+425 + (SCREEN_HEIGHT / 20)) && y>=SCREEN_HEIGHT / 22+425)   // Chaayos
                && inMain){
                        enterChaayos = true;
                        enterRestaurant = true;
                        x = SCREEN_WIDTH - 290;
                        y = 150;
                        inMain = false;
                        inMain = false;
                        enterHostel = false;
                        inLargeGround = false;
                        enterSAC = false;
                        enterMasalaMix = false;
                        enterRajdhani = false;
                        enterShiru = false;
                        enterAmul = false;
                        enterNescafe = false;
                        enterCCD = false;
                        enterStaffCanteen = false;
                        enterDilli16 = false;
                        enterLibrary = false;
                        inLHC = false;
                        inLHC108 = false;
                        inLHC114 = false;
                        inLHC325 = false;
                        isSleeping = false;
                        takenYulu = false;
                        inVolleyCourt = false;
                        inTennisCourt = false;
                        inLargeGround = false;
                        playaudio("/Users/eshan/Downloads/enter-sound.wav") ;
                }
                
               else if (!enterRestaurant&& 
                        // enter shiru
                ( x>= SCREEN_WIDTH / 22+500 && x<=( SCREEN_WIDTH / 22+450 + (SCREEN_WIDTH / 18)) && y<=(SCREEN_HEIGHT / 22+695+ (SCREEN_HEIGHT / 18)) && y>=SCREEN_HEIGHT / 22+695  ) //Shiru Cafe
                && inMain){
                        enterShiru = true;
                        enterRestaurant = true;
                        inMain = false;
                        enterHostel = false;
                        inLargeGround = false;
                        enterSAC = false;
                        enterMasalaMix = false;
                        enterRajdhani = false;
                        enterChaayos = false;
                        enterAmul = false;
                        enterNescafe = false;
                        enterCCD = false;
                        enterStaffCanteen = false;
                        enterDilli16 = false;
                        enterLibrary = false;
                        inLHC = false;
                        inLHC108 = false;
                        inLHC114 = false;
                        inLHC325 = false;
                        isSleeping = false;
                        takenYulu = false;
                        inVolleyCourt = false;
                        inTennisCourt = false;
                        inLargeGround = false;
                        x = SCREEN_WIDTH - 290;
                        y = 150;
                        inMain = false;
                        playaudio("/Users/eshan/Downloads/enter-sound.wav") ;
                }


                else if (!enterRestaurant&&
                        // enter amul
                (x>= SCREEN_WIDTH / 22+630 && x<=( SCREEN_WIDTH / 22+580 + (SCREEN_WIDTH / 18)) && y<=(SCREEN_HEIGHT / 22+695 + (SCREEN_HEIGHT / 18)) && y>=SCREEN_HEIGHT / 22+695 )  //Amul
                && inMain){
                        enterAmul = true;
                        enterRestaurant = true;
                        inMain = false;
                        enterHostel = false;
                        inLargeGround = false;
                        enterSAC = false;
                        enterMasalaMix = false;
                        enterRajdhani = false;
                        enterChaayos = false;
                        enterShiru = false;
                        enterNescafe = false;
                        enterCCD = false;
                        enterStaffCanteen = false;
                        enterDilli16 = false;
                        enterLibrary = false;
                        inLHC = false;
                        inLHC108 = false;
                        inLHC114 = false;
                        inLHC325 = false;
                        isSleeping = false;
                        takenYulu = false;
                        inVolleyCourt = false;
                        inTennisCourt = false;
                        inLargeGround = false;
                        x = SCREEN_WIDTH - 290;
                        y = 150;
                        inMain = false;
                        playaudio("/Users/eshan/Downloads/enter-sound.wav") ;
                }


                else if (!enterRestaurant&&
                (x>= SCREEN_WIDTH / 22+780 && x<=( SCREEN_WIDTH / 22+720 + (SCREEN_WIDTH / 18)) && y<=(SCREEN_HEIGHT / 22+695 + (SCREEN_HEIGHT / 18)) && y>=SCREEN_HEIGHT / 22+695)   //Nescafe
                && inMain){
                        // enter nescafe
                        enterNescafe = true;
                        enterRestaurant = true;
                        inMain = false;
                        enterHostel = false;
                        inLargeGround = false;
                        enterSAC = false;
                        enterMasalaMix = false;
                        enterRajdhani = false;
                        enterChaayos = false;
                        enterShiru = false;
                        enterAmul = false;
                        enterCCD = false;
                        enterStaffCanteen = false;
                        enterDilli16 = false;
                        enterLibrary = false;
                        inLHC = false;
                        inLHC108 = false;
                        inLHC114 = false;
                        inLHC325 = false;
                        isSleeping = false;
                        takenYulu = false;
                        inVolleyCourt = false;
                        inTennisCourt = false;
                        inLargeGround = false;
                        x = SCREEN_WIDTH - 290;
                        y = 150;
                        inMain = false;
                        playaudio("/Users/eshan/Downloads/enter-sound.wav") ;
                }


                else if (!enterRestaurant&&
                (x>= SCREEN_WIDTH / 22+880 && x<=( SCREEN_WIDTH / 22+880 + (SCREEN_WIDTH / 15)) && y<=(SCREEN_HEIGHT / 22+690 + (SCREEN_HEIGHT / 8)) && y>=SCREEN_HEIGHT / 22+780 )  //CCD
                && inMain){
                        // enter ccd
                        enterCCD = true;
                        enterRestaurant = true;
                        inMain = false;
                        enterHostel = false;
                        inLargeGround = false;
                        enterSAC = false;
                        enterMasalaMix = false;
                        enterRajdhani = false;
                        enterChaayos = false;
                        enterShiru = false;
                        enterAmul = false;
                        enterNescafe = false;
                        enterStaffCanteen = false;
                        enterDilli16 = false;
                        enterLibrary = false;
                        inLHC = false;
                        inLHC108 = false;
                        inLHC114 = false;
                        inLHC325 = false;
                        isSleeping = false;
                        takenYulu = false;
                        inVolleyCourt = false;
                        inTennisCourt = false;
                        inLargeGround = false;
                        x = SCREEN_WIDTH - 290;
                        y = 150;
                        inMain = false;
                        playaudio("/Users/eshan/Downloads/enter-sound.wav") ;
                }


                else if (!enterRestaurant&&
                (x>= SCREEN_WIDTH / 22+80 && x<=( SCREEN_WIDTH / 22 + 110) && y<=(SCREEN_HEIGHT / 22+590 + (SCREEN_HEIGHT / 6)) && y>=SCREEN_HEIGHT / 22+725)  //Staff Canteen
                && inMain){
                        // enter staff canteen
                        enterStaffCanteen = true;
                        enterRestaurant = true;

                        inMain = false;
                        enterHostel = false;
                        inLargeGround = false;
                        enterSAC = false;
                        enterMasalaMix = false;
                        enterRajdhani = false;
                        enterChaayos = false;
                        enterShiru = false;
                        enterAmul = false;
                        enterNescafe = false;
                        enterCCD = false;
                        enterDilli16 = false;
                        enterLibrary = false;
                        inLHC = false;
                        inLHC108 = false;
                        inLHC114 = false;
                        inLHC325 = false;
                        isSleeping = false;
                        takenYulu = false;
                        inVolleyCourt = false;
                        inTennisCourt = false;
                        inLargeGround = false;
                        x = SCREEN_WIDTH - 290;
                        y = 150;
                        inMain = false;
                        playaudio("/Users/eshan/Downloads/enter-sound.wav") ;
                }


                else if (!enterRestaurant&&
                        // enter dilli16
                (x>= SCREEN_WIDTH / 22+95+130+40+160 && x<=( SCREEN_WIDTH / 22+95+130+40+160 + (SCREEN_WIDTH / 15)) && y<=(SCREEN_HEIGHT / 22+134 + (SCREEN_HEIGHT / 20)) && y>=SCREEN_HEIGHT / 22+134 ) //Dilli-16
                && inMain){
                        enterDilli16 = true;
                        enterRestaurant = true;

                        inMain = false;
                        enterHostel = false;
                        inLargeGround = false;
                        enterSAC = false;
                        enterMasalaMix = false;
                        enterRajdhani = false;
                        enterChaayos = false;
                        enterShiru = false;
                        enterAmul = false;
                        enterNescafe = false;
                        enterCCD = false;
                        enterStaffCanteen = false;
                        enterLibrary = false;
                        inLHC = false;
                        inLHC108 = false;
                        inLHC114 = false;
                        inLHC325 = false;
                        isSleeping = false;
                        takenYulu = false;
                        inVolleyCourt = false;
                        inTennisCourt = false;
                        inLargeGround = false;
                        x = SCREEN_WIDTH - 290;
                        y = 150;
                        inMain = false;
                        playaudio("/Users/eshan/Downloads/enter-sound.wav") ;
                }




        







                // exit from restaurants

                /*else if(enterRestaurant && x>=SCREEN_WIDTH*0.75 && x<=0.9*SCREEN_WIDTH && y>=0.09*SCREEN_HEIGHT && y<=0.21*SCREEN_HEIGHT){
                        enterRestaurant = false;
                        inMain = true;
                        x = (SCREEN_WIDTH / 22+95+130) + 10;
                        y = (SCREEN_HEIGHT / 22+425) + 10 ;
                }
                */

                else if (x>=SCREEN_WIDTH*0.75 && x<=0.9*SCREEN_WIDTH && y>=0.09*SCREEN_HEIGHT && y<=0.21*SCREEN_HEIGHT
                && enterMasalaMix){
                        enterRestaurant = false;
                        enterMasalaMix = false;
                        inMain = true;
                        x = SCREEN_WIDTH / 22+95+130 + 35;
                        y = SCREEN_HEIGHT / 22+425+ 10 ;
                        playaudio("/Users/eshan/Downloads/enter-sound.wav") ;
                }

                else if (x>=SCREEN_WIDTH*0.75 && x<=0.9*SCREEN_WIDTH && y>=0.09*SCREEN_HEIGHT && y<=0.21*SCREEN_HEIGHT
                && enterRajdhani){
                        enterRestaurant = false;
                        enterRajdhani = false;
                        inMain = true;
                        x = (SCREEN_WIDTH / 22+95+130+100 + 35);
                        y = SCREEN_HEIGHT / 22+425 + 10 ;
                        playaudio("/Users/eshan/Downloads/enter-sound.wav") ;
                }

                else if (x>=SCREEN_WIDTH*0.75 && x<=0.9*SCREEN_WIDTH && y>=0.09*SCREEN_HEIGHT && y<=0.21*SCREEN_HEIGHT
                && enterChaayos){
                        enterRestaurant = false;
                        enterChaayos = false;
                        inMain = true;
                        x = SCREEN_WIDTH / 22+95+130+200 + 35;
                        y = SCREEN_HEIGHT / 22+425 + 10 ;
                        playaudio("/Users/eshan/Downloads/enter-sound.wav") ;
                }

                else if (x>=SCREEN_WIDTH*0.75 && x<=0.9*SCREEN_WIDTH && y>=0.09*SCREEN_HEIGHT && y<=0.21*SCREEN_HEIGHT
                && enterShiru){
                        enterRestaurant = false;
                        enterShiru = false;
                        inMain = true;
                        x = SCREEN_WIDTH / 22+480 + 20;
                        y = SCREEN_HEIGHT / 22+695 + 5 ;
                        playaudio("/Users/eshan/Downloads/enter-sound.wav") ;
                }

                else if (x>=SCREEN_WIDTH*0.75 && x<=0.9*SCREEN_WIDTH && y>=0.09*SCREEN_HEIGHT && y<=0.21*SCREEN_HEIGHT
                && enterAmul){
                        enterRestaurant = false;
                        enterAmul = false;
                        inMain = true;
                        x = SCREEN_WIDTH / 22+610 + 20;
                        y = SCREEN_HEIGHT / 22+695 + 5 ;
                        playaudio("/Users/eshan/Downloads/enter-sound.wav") ;
                }

                else if (x>=SCREEN_WIDTH*0.75 && x<=0.9*SCREEN_WIDTH && y>=0.09*SCREEN_HEIGHT && y<=0.21*SCREEN_HEIGHT
                && enterNescafe){
                        enterRestaurant = false;
                        enterNescafe = false;
                        inMain = true;
                        x = SCREEN_WIDTH / 22+760 + 20;
                        y = SCREEN_HEIGHT / 22+695+ 5 ;
                        playaudio("/Users/eshan/Downloads/enter-sound.wav") ;
                }


                else if (x>=SCREEN_WIDTH*0.75 && x<=0.9*SCREEN_WIDTH && y>=0.09*SCREEN_HEIGHT && y<=0.21*SCREEN_HEIGHT
                && enterCCD){
                        enterRestaurant = false;
                        enterCCD = false;
                        inMain = true;
                        x = SCREEN_WIDTH / 22+860 + 60;
                        y = SCREEN_HEIGHT / 22+760+ 47 ;
                        playaudio("/Users/eshan/Downloads/enter-sound.wav") ;
                }


                else if (x>=SCREEN_WIDTH*0.75 && x<=0.9*SCREEN_WIDTH && y>=0.09*SCREEN_HEIGHT && y<=0.21*SCREEN_HEIGHT
                && enterStaffCanteen){
                        enterRestaurant = false;
                        enterStaffCanteen = false;
                        inMain = true;
                        x = SCREEN_WIDTH / 22+60 + 30;
                        y = SCREEN_HEIGHT / 22+735 + 14;
                        playaudio("/Users/eshan/Downloads/enter-sound.wav") ;
                }


                else if (x>=SCREEN_WIDTH*0.75 && x<=0.9*SCREEN_WIDTH && y>=0.09*SCREEN_HEIGHT && y<=0.21*SCREEN_HEIGHT
                && enterDilli16){
                        enterRestaurant = false;
                        enterDilli16 = false;
                        inMain = true;
                        x = SCREEN_WIDTH / 22+95+130+40+160 + 40;
                        y = SCREEN_HEIGHT / 22+134 + 13;
                        playaudio("/Users/eshan/Downloads/enter-sound.wav") ;
                }


                //Counter
                else if(enterRestaurant && x>=SCREEN_WIDTH*0.03 && x<=0.68*SCREEN_WIDTH && y>=0.2*SCREEN_HEIGHT && y<=0.3*SCREEN_HEIGHT){
                        
                        if(money<20){
                                insufficientMoney = true;
                        }
                        else{
                        happiness = min(happiness+10, 100);
                        health-=10;
                        if(health<=0){
                                hospitalize();
                        }
                        energy=min(energy+10, 100);
                        money-=20;
                        }
                        playaudio("/Users/eshan/Downloads/click-sound.wav") ;
                }

        
                

                //SAC



                // enter into SAC

                else if (x>=(0) && x<=SCREEN_WIDTH / 10 && y<=SCREEN_HEIGHT / 8  + SCREEN_HEIGHT / 22+220  && y>=SCREEN_HEIGHT / 22+220 && inMain){
                        enterSAC = true;
                        x = SCREEN_WIDTH*0.09;
                        y = 0.75*SCREEN_HEIGHT;
                        inMain = false;
                        playaudio("/Users/eshan/Downloads/enter-sound.wav") ;
                }
                // exit from SAC

                else if(enterSAC && x>=SCREEN_WIDTH*0.06 && x<=0.24*SCREEN_WIDTH && y>=0.72*SCREEN_HEIGHT && y<=0.93*SCREEN_HEIGHT){
                        enterSAC = false;
                        inMain = true;
                        x = SCREEN_WIDTH / 20+60;
                        y = SCREEN_HEIGHT / 22+265 ;
                        playaudio("/Users/eshan/Downloads/enter-sound.wav") ;
                }

                //Music 

                else if(enterSAC && x>=SCREEN_WIDTH*0.14 && x<=0.34*SCREEN_WIDTH && y>=0.34*SCREEN_HEIGHT && y<=0.52*SCREEN_HEIGHT){
                        
                        happiness = min(100,happiness+10);
                        energy-=10;
                        if(energy<=0){
                                hospitalize();
                        }
                        playaudio("/Users/eshan/Downloads/click-sound.wav") ;

                        
                }

                //GYM

                else if(enterSAC && x>=SCREEN_WIDTH*0.65 && x<=0.83*SCREEN_WIDTH && y>=0.1*SCREEN_HEIGHT && y<=0.27*SCREEN_HEIGHT){
                        temp9Clip = 0;
                        happiness = min(100,happiness+10);
                        health=min(health+10, 100);
                        energy-=10;
                        if(energy<=0){
                                hospitalize();
                        }
                        playaudio("/Users/eshan/Downloads/click-sound.wav") ;

                        
                }


                //Badminton Court

                else if(enterSAC && x>=SCREEN_WIDTH*0.33 && x<=0.56*SCREEN_WIDTH && y>=0*SCREEN_HEIGHT && y<=0.12*SCREEN_HEIGHT){
                        temp10Clip = 0;
                        happiness = min(100,happiness+10);
                        health=min(health+10, 100);
                        energy-=10;
                        if(energy<=0){
                                hospitalize();
                        }
                        playaudio("/Users/eshan/Downloads/click-sound.wav") ;

                        
                }





                //Library



                // enter into Library

                else if ( y<=990  && y>=970 && x>=700 && x<=800&& inMain){          // SUBSTITUTE ACCURATE COORDINATES ACCORDING TO INTERROAD POSITION OF LIBRARY
                        enterLibrary = true;
                        x = SCREEN_WIDTH*0.04;
                        y = 0.58*SCREEN_HEIGHT;
                        inMain = false;
                        playaudio("/Users/eshan/Downloads/enter-sound.wav") ;

                }
                // exit from Library

                else if(enterLibrary && x>=1350 && x<=1490 && y<=520 && y>=450){
                        enterLibrary = false;
                        inMain = true;
                        x = 750;                  //ACCORDINGLY SET COORDINATES OF LIBRARY INTERROAD 
                        y = 980 ;
                }

                //Chair 
                // change view to study
                else if(enterLibrary && x>=550 && x<=800 && y>=450 && y<=700){
                        
                        enterLibrary = false;
                        isStudying = true;
                

                }
                // studing in library
                else if(isStudying){
                        enterLibrary = true;
                        isStudying = false;
                }


        }

        void changeYulu(){
                // initially did not have yulu
                if (money>0){

                        if(x>=138 && x<=215 && y>=300 && y<=325){
                           if(!takenYulu){
                                takenYulu = true;
                                speed+=1;
                           }
                           else{   // already had yulu now leaving it
                                takenYulu = false;
                                speed-=1;
                           }     
                        }

                        if(y>=420 && y<=465 && x<=255 && x>=230){
                           if(!takenYulu){
                                takenYulu = true;
                                speed+=1;
                           }
                           else{   // already had yulu now leaving it
                                takenYulu = false;
                                speed-=1;
                           }     
                        }

                        if(y>=630 && y<=670 && x<=255 && x>=230){
                           if(!takenYulu){
                                takenYulu = true;
                                speed+=1;
                           }
                           else{   // already had yulu now leaving it
                                takenYulu = false;
                                speed-=1;
                           }     
                        }

                        if(y>=820 && y<=854 && x<=255 && x>=230){
                           if(!takenYulu){
                                takenYulu = true;
                                speed+=1;
                           }
                           else{   // already had yulu now leaving it
                                takenYulu = false;
                                speed-=1;
                           }     
                        }

                        if(x>=947 && x<=994 && y<=180 && y>=165){
                           if(!takenYulu){
                                takenYulu = true;
                                speed+=1;
                           }
                           else{   // already had yulu now leaving it
                                takenYulu = false;
                                speed-=1;
                           }     
                        }
                        if(y<=560 && y>=530 && x<=640 && x>=595){
                           if(!takenYulu){
                                takenYulu = true;
                                speed+=1;
                           }
                           else{   // already had yulu now leaving it
                                takenYulu = false;
                                speed-=1;
                           }     
                        }

                        if(y<=990 && y>=955 && x>=930 && x<=980){
                           if(!takenYulu){
                                takenYulu = true;
                                speed+=1;
                           }
                           else{   // already had yulu now leaving it
                                takenYulu = false;
                                speed-=1;
                           }     
                        }
                }
                else if(money<=0 && y<=990 && y>=955 && x>=930 && x<=980 || y<=560 && y>=530 && x<=640 && x>=595 || x>=947 && x<=994 && y<=180 && y>=165 || y>=820 && y<=854 && x<=255 && x>=230 || y>=630 && y<=670 && x<=255 && x>=230 || y>=420 && y<=465 && x<=255 && x>=230 || x>=138 && x<=215 && y>=300 && y<=325){
                        insufficientMoney = true;

                }
                
        }

        void renderPlayer(){
                SDL_Rect player1 = {x,y,30,30};
                if(lastStepDirection==0)
                    SDL_RenderCopy(gRenderer,colorTexFront,NULL,&player1);
                else if(lastStepDirection==1)
                    SDL_RenderCopy(gRenderer,colorTexBack,NULL,&player1);
                else if(lastStepDirection==2)
                    SDL_RenderCopy(gRenderer,colorTexLeft,NULL,&player1);
                else if(lastStepDirection==3)
                    SDL_RenderCopy(gRenderer,colorTexRight,NULL,&player1);
        }

};



//The window we'll be rendering to




bool init(){


        bool success = true;
        if(SDL_Init(SDL_INIT_VIDEO)<0){
                success = false;
        }

        else{
                //Set texture filtering to linear
                if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
                {
                        printf( "Warning: Linear texture filtering not enabled!" );
                }

                //Create window
                gWindow = SDL_CreateWindow( "CLIENT", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
                if( gWindow == NULL )
                {
                        printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
                        success = false;
                }
                else
                {
                        //Create renderer for window
                        gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED );
                        if( gRenderer == NULL )
                        {
                                printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
                                success = false;
                        }
                        else
                        {
                                //Initialize renderer color
                                SDL_SetRenderDrawColor( gRenderer, 0x00, 0x00, 0x00, 0x00 );

                                //Initialize PNG loading
                                int imgFlags = IMG_INIT_PNG;
                                if( !( IMG_Init( imgFlags ) & imgFlags ) )
                                {
                                        printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
                                        success = false;
                                }
                        }
                }


        }
        return success;

}
void close()
{
        //Free loaded image
        SDL_DestroyTexture( gTexture );
        SDL_DestroyTexture( imageTexture );
        gTexture = NULL;
        imageTexture = NULL;

        //Destroy window        
        SDL_DestroyRenderer( gRenderer );
        SDL_DestroyWindow( gWindow );
        gWindow = NULL;
        gRenderer = NULL;
        //Quit SDL subsystems
        IMG_Quit();
        SDL_Quit();
}


int main(int argc, char const *argv[])
{
        

        if (!init()){
                printf ("failed to initialize\n");
        }
        else{
                int sockfd, connfd;
            struct sockaddr_in servaddr, cli;
           
            // socket create and verification
            sockfd = socket(AF_INET, SOCK_STREAM, 0);
            if (sockfd == -1) {
                printf("socket creation failed...\n");
                exit(0);
            }
            else
                printf("Socket successfully created..\n");
            bzero(&servaddr, sizeof(servaddr));
           
            // assign IP, PORT
            servaddr.sin_family = AF_INET;
            servaddr.sin_addr.s_addr = inet_addr("10.184.15.148");
            servaddr.sin_port = htons(PORT);
           
            // connect the client socket to server socket
            if (connect(sockfd, (SA*)&servaddr, sizeof(servaddr)) != 0) {
                printf("connection with the server failed...\n");
                exit(0);
            }
            else
                printf("connected to the server..\n");
            char buff[MAX];
            int n;
            string s1,s2,s3;
                start = SDL_GetTicks();
                // hostel textures
                SDL_Texture* tileTex = loadFromFile("tile.png");
                SDL_Texture* ttableTex = loadFromFile("tabletennis.png");
                SDL_Texture* messTex = loadFromFile("mess.png");
                SDL_Texture* grassTex = loadFromFile("grass.png");
                SDL_Texture* rabbitTex = loadFromFile("rabbit.png");
                SDL_Texture* rabbitfTex = loadFromFile("rabbitf.png");
                SDL_Texture* rabbitthTex = loadFromFile("rabbitth.png");
                SDL_Texture* roomTex = loadFromFile("room.png");
                SDL_Texture* restaurantTex = loadFromFile("restaurant.png");
                SDL_Texture* tree_topTex = loadFromFile("tree-top.png");
                SDL_Texture* tree_leftTex = loadFromFile("tree-left.png");
                SDL_Texture* tree_rightTex = loadFromFile("tree-right.png");
                SDL_Texture* hostelgateTex = loadFromFile("hostelgate.png");
                SDL_Texture* caretakerTex = loadFromFile("CARETAKEROFFICE.png");
                SDL_Texture* washroomTex = loadFromFile("washroom.png");
                SDL_Texture* entry_exitTex = loadFromFile("hostelgate.png");

                        // sleep
                SDL_Texture* sleepTex = loadFromFile("sleeping.png");
                ////////////////
                // main textures
                SDL_Texture* nilgiriTex=loadFromFile("nilgiri.png"); 
                SDL_Texture* karakoramTex = loadFromFile("karakoram.png");
                SDL_Texture* aravaliTex = loadFromFile("aravali.png");
                SDL_Texture* jwalaTex = loadFromFile("jwalamukhi.png");
                SDL_Texture* kumaonTex = loadFromFile("kumaon.png");
                SDL_Texture* vidyanchalTex = loadFromFile("vidyanchal.png");
                SDL_Texture* deli16Tex  = loadFromFile("deli16.png");
                SDL_Texture* tennisCourtTex = loadFromFile("tennis_court.png");
                SDL_Texture* volleyBallCourtTex = loadFromFile("volleyball.png");
                SDL_Texture* shivalikTex = loadFromFile("shivalik.png");
                SDL_Texture* zanskarTex = loadFromFile("zanskar.png");
                SDL_Texture* masalaMixTex = loadFromFile("masalamix.png");
                SDL_Texture* rajdhaniTex = loadFromFile("rajdhani.png");
                SDL_Texture* chaayosTex = loadFromFile("chaayos.png");
                SDL_Texture* hospitalTex = loadFromFile("iitd-hospital.png");
                SDL_Texture* bhartiTex = loadFromFile("bharti.png");
                SDL_Texture* largeGroundTex = loadFromFile("grass.png");
                SDL_Texture* gtree1Tex = loadFromFile("tree-top.png");
                SDL_Texture* gtree2Tex = loadFromFile("tree-top.png");
                SDL_Texture* gtree3Tex = loadFromFile("tree-top.png");
                SDL_Texture* gtree4Tex = loadFromFile("tree-top.png");
                SDL_Texture* gtree5Tex = loadFromFile("tree-top.png");
                SDL_Texture* gtree6Tex = loadFromFile("tree-top.png");
                SDL_Texture* gtree7Tex = loadFromFile("tree-top.png");
                SDL_Texture* gtree8Tex = loadFromFile("tree-top.png");
                SDL_Texture* gtree9Tex = loadFromFile("tree-top.png");
                SDL_Texture* gtree10Tex = loadFromFile("tree-top.png");
                SDL_Texture* gtree11Tex = loadFromFile("tree-top.png");
                SDL_Texture* gtree12Tex = loadFromFile("tree-top.png");
                SDL_Texture* staffCanteenTex = loadFromFile("staffcanteen.png");
                SDL_Texture* LHCTex = loadFromFile("lecturehall.png");
                SDL_Texture* dograHallTex = loadFromFile("dograhall.png");
                SDL_Texture* cscTex = loadFromFile("csc.png");
                SDL_Texture* satpuraTex = loadFromFile("satpura.png");
                SDL_Texture* girnarTex = loadFromFile("girnar.png");
                SDL_Texture* udaigiriTex = loadFromFile("udaigiri.png");
                SDL_Texture* shiruTex = loadFromFile("shirucafe.png");
                SDL_Texture* amulTex = loadFromFile("amul.png");
                SDL_Texture* nescafeTex = loadFromFile("nescafe.png");
                SDL_Texture* ccdTex = loadFromFile("ccd.png");
                SDL_Texture* clibraryTex = loadFromFile("centrallibrary.png");
                SDL_Texture* libraryinsideTex = loadFromFile("library-inside-view.png");
                SDL_Texture* mainBuildingTex = loadFromFile("mainbuilding.png");
                SDL_Texture* interConnectingRoadsTex = loadFromFile("interconnecting.png");
                SDL_Texture* sacCircleTex = loadFromFile("saccircle.png");
                SDL_Texture* vrTex = loadFromFile("verticalroad.png");
                SDL_Texture* hr1Tex = loadFromFile("horizontalroad.png");
                SDL_Texture* hr2Tex = loadFromFile("horizontalroad2.png");
                SDL_Texture* tpTex = loadFromFile("tpoint.png");
                SDL_Texture* sacTex = loadFromFile("SAC.png");
                SDL_Texture* SACinsideTex = loadFromFile("badminton1.png");
                SDL_Texture* interConnectingRoads2Tex = loadFromFile("interconnecting2.png");
                SDL_Texture* exitTex = loadFromFile("exit.png");
                SDL_Texture* angryProfessorTex = loadFromFile("angryProf.png");
                SDL_Texture* hungryDogTex = loadFromFile("dog.png");
                SDL_Texture* yuluTex = loadFromFile("yulu.png");

                SDL_Texture* workerSprites = loadFromFile("workersprites.png");

                SDL_Texture* ttframe2Tex = loadFromFile("ttframe2.png");
                SDL_Texture* ttframe3Tex = loadFromFile("ttframe3.png");
                SDL_Texture* ttframe4Tex = loadFromFile("ttframe4.png");
                SDL_Texture* ttframe5Tex = loadFromFile("ttframe5.png");
                SDL_Texture* ttframe6Tex = loadFromFile("ttframe6.png");
                SDL_Texture* ttframe7Tex = loadFromFile("ttframe7.png");
                SDL_Texture* ttframe8Tex = loadFromFile("ttframe8.png");
                SDL_Texture* ttframe9Tex = loadFromFile("ttframe9.png");
                SDL_Texture* ttframe10Tex = loadFromFile("ttframe10.png");

                SDL_Texture* messframe1Tex = loadFromFile("messframe1.png");
                SDL_Texture* messframe2Tex = loadFromFile("messframe2.png");
                SDL_Texture* messframe3Tex = loadFromFile("messframe3.png");
                SDL_Texture* messframe4Tex = loadFromFile("messframe4.png");

                SDL_Texture* tennisframe1Tex = loadFromFile("tennisframe1.png");
                SDL_Texture* tennisframe2Tex = loadFromFile("tennisframe2.png");
                SDL_Texture* tennisframe3Tex = loadFromFile("tennisframe3.png");
                SDL_Texture* tennisframe4Tex = loadFromFile("tennisframe4.png");
                SDL_Texture* tennisframe5Tex = loadFromFile("tennisframe5.png");
                SDL_Texture* tennisframe6Tex = loadFromFile("tennisframe6.png");

                SDL_Texture* volleyballframeTex1 = loadFromFile("volleyballInner.png");
                SDL_Texture* volleyballframeTex2 = loadFromFile("volleyballframe2.png");
                SDL_Texture* volleyballframeTex3 = loadFromFile("volleyballframe3.png");
                SDL_Texture* volleyballframeTex4 = loadFromFile("volleyballframe4.png");
                SDL_Texture* volleyballframeTex5 = loadFromFile("volleyballframe5.png");
                SDL_Texture* volleyballframeTex6 = loadFromFile("volleyballframe6.png");

                SDL_Texture* footballframe1Tex = loadFromFile("footballframe1.png");
                SDL_Texture* footballframe2Tex = loadFromFile("footballframe2.png");
                SDL_Texture* footballframe3Tex = loadFromFile("footballframe3.png");
                SDL_Texture* footballframe4Tex = loadFromFile("footballframe4.png");
                SDL_Texture* footballframe5Tex = loadFromFile("footballframe5.png");
                SDL_Texture* footballframe6Tex = loadFromFile("footballframe6.png");

                SDL_Texture* cricketframe1Tex = loadFromFile("cricketframe1.png");
                SDL_Texture* cricketframe2Tex = loadFromFile("cricketframe2.png");
                SDL_Texture* cricketframe3Tex = loadFromFile("cricketframe3.png");
                SDL_Texture* cricketframe4Tex = loadFromFile("cricketframe4.png");
                SDL_Texture* cricketframe5Tex = loadFromFile("cricketframe5.png");
                SDL_Texture* cricketframe6Tex = loadFromFile("cricketframe6.png");

                SDL_Texture* hockeyframe1Tex = loadFromFile("hockeyframe1.png");
                SDL_Texture* hockeyframe2Tex = loadFromFile("hockeyframe2.png");
                SDL_Texture* hockeyframe3Tex = loadFromFile("hockeyframe3.png");
                SDL_Texture* hockeyframe4Tex = loadFromFile("hockeyframe4.png");
                SDL_Texture* hockeyframe5Tex = loadFromFile("hockeyframe5.png");
                SDL_Texture* hockeyframe6Tex = loadFromFile("hockeyframe6.png");
                SDL_Texture* hockeyframe7Tex = loadFromFile("hockeyframe7.png");
                SDL_Texture* hockeyframe8Tex = loadFromFile("hockeyframe8.png");
                SDL_Texture* hockeyframe9Tex = loadFromFile("hockeyframe9.png");

                SDL_Texture* badmintonframeTex1 = loadFromFile("badminton1.png");
                SDL_Texture* badmintonframeTex2 = loadFromFile("badminton2.png");
                SDL_Texture* badmintonframeTex3 = loadFromFile("badminton3.png");
                SDL_Texture* badmintonframeTex4 = loadFromFile("badminton4.png");
                SDL_Texture* badmintonframeTex5 = loadFromFile("badminton5.png");


                SDL_Texture* insufficientMoneyTex = loadFromFile("lessmoney.png");
                SDL_Rect arr[3];
                arr[0] = {0,0,700/3,700};
                arr[1] = {700/3,0,700/3,700};
                arr[2] = {1400/3,0,700/3,700};


                SDL_Rect textRect = {SCREEN_WIDTH-160,800,140,50};
                // large ground textures
                SDL_Texture* largeGroundInnerTex = loadFromFile("largegroundInner.png");

                // tennisCourt
                SDL_Texture* tennisCourtInnerTex = loadFromFile("tennisInner.png");

                // volley ball court
                SDL_Texture* volleyCourtInnerTex = loadFromFile("volleyballInner.png");

                // LHC
                SDL_Texture* LHCInnerTex = loadFromFile("lhcInner.png");

                //LHC108
                SDL_Texture* LH108Tex = loadFromFile("LH108.png");

                //LHC114
                SDL_Texture* LHC114Tex = loadFromFile("LH114.png");

                //LHC325
                SDL_Texture* LHC325Tex = loadFromFile("LH325.png");

                // yulu top
                SDL_Texture* yuluTopTex = loadFromFile("yulutop.png");


                // studying in lib
                SDL_Texture* studyTex = loadFromFile("study.png");

                // gym texture

                SDL_Texture* gymframeTex1 = loadFromFile("gymframe1.png");
                SDL_Texture* gymframeTex2 = loadFromFile("gymframe2.png");

                Player player1 = Player(SCREEN_WIDTH-600,175,"purple");
                Player player2 = Player(60,175,"pink");
                bool quit = false;

                SDL_Event e;


                while(!quit){
                        
                        // cout<<player1.lastStepDirection<<"\n";

                        // player1 is bankerupt
                        if(player1.money ==0 && !player1.bankrupt){
                                player1.takenYulu = false;
                                player1.speed-=1;
                                player1.bankrupt = true;
                        }
                        if(player1.money>0){
                                player1.bankrupt = false;
                        }

        SDL_SetRenderDrawColor(gRenderer,0x00,0x00,0x00,0x00);
        SDL_RenderClear(gRenderer);
            

            bzero(buff, sizeof(buff));
                                n = 0;
                                s1 = to_string(player1.x);
                                buff[0] = s1[0];
                                buff[1] = s1[1];
                                buff[2] = s1[2];
                                buff[3] = s1[3];
                                s2 = to_string(player1.y);
                                buff[4] = s2[0];
                                buff[5] = s2[1];
                                buff[6] = s2[2];
                                buff[7] = s2[3];
                                s3 = to_string(player1.lastStepDirection);
                                buff[8] = s3[0];
                                buff[9] = s3[1];
                                buff[10] = s3[2];
                                buff[11] = s3[3];
                                if(player1.inMain){
                                        buff[12] = '1';
                                }
                                else{
                                        buff[12]='0';
                                }

                                if(player1.enterHostel){
                                        buff[13] = '1';
                                }
                                else{
                                        buff[13]='0';
                                }
                                if(player1.inLargeGround){
                                        buff[14] = '1';
                                }
                                else{
                                        buff[14]='0';
                                }

                                if(player1.inTennisCourt){
                                        buff[15] = '1';
                                }
                                else{
                                        buff[15]='0';
                                }
                                if(player1.inVolleyCourt){
                                        buff[16] = '1';
                                }
                                else{
                                        buff[16]='0';
                                }
                                if(player1.inLHC){
                                        buff[17] = '1';
                                }
                                else{
                                        buff[17]='0';
                                }
                                if(player1.inLHC108){
                                        buff[18] = '1';
                                }
                                else{
                                        buff[18]='0';
                                }
                                if(player1.inLHC114){
                                        buff[19] = '1';
                                }
                                else{
                                        buff[19]='0';
                                }
                                if(player1.inLHC325){
                                        buff[20] = '1';
                                }
                                else{
                                        buff[20]='0';
                                }
                                if(player1.enterSAC){
                                        buff[21] = '1';
                                }
                                else{
                                        buff[21]='0';
                                }
                                if(player1.enterRestaurant){
                                        buff[22] = '1';
                                }
                                else{
                                        buff[22]='0';
                                }
                                if(player1.enterMasalaMix){
                                        buff[23] = '1';
                                }
                                else{
                                        buff[23]='0';
                                }
                                if(player1.enterRajdhani){
                                        buff[24] = '1';
                                }
                                else{
                                        buff[24]='0';
                                }
                                if(player1.enterChaayos){
                                        buff[25] = '1';
                                }
                                else{
                                        buff[25]='0';
                                }
                                if(player1.enterShiru){
                                        buff[26] = '1';
                                }
                                else{
                                        buff[26]='0';
                                }
                                if(player1.enterAmul){
                                        buff[27] = '1';
                                }
                                else{
                                        buff[27]='0';
                                }
                                if(player1.enterNescafe){
                                        buff[28] = '1';
                                }
                                else{
                                        buff[28]='0';
                                }
                                if(player1.enterCCD){
                                        buff[29] = '1';
                                }
                                else{
                                        buff[29]='0';
                                }
                                if(player1.enterStaffCanteen){
                                        buff[30] = '1';
                                }
                                else{
                                        buff[30]='0';
                                }
                                if(player1.enterDilli16){
                                        buff[31] = '1';
                                }
                                else{
                                        buff[31]='0';
                                }

                                if(player1.enterLibrary){
                                        buff[32] = '1';
                                }
                                else{
                                        buff[32]='0';
                                }
                                if(player1.isSleeping){
                                        buff[33] = '1';
                                }
                                else{
                                        buff[33]='0';
                                }
                                if(player1.isStudying){
                                        buff[34] = '1';
                                }
                                else{
                                        buff[34]='0';
                                }
                                // cout<<"IN CLIENT SIDE\n";
                                // cout<<s1<<" "<<s2<<"\n";
                                // cout<<buff[1]<<"\n";
                                write(sockfd, buff, sizeof(buff));
                                bzero(buff, sizeof(buff));
                                
                                        read(sockfd, buff, sizeof(buff));
                                
                                // cout<<"works till here\n";
                                s1="";
                                s1+=buff[0];
                                s1+=buff[1];
                                s1+=buff[2];
                                s1+=buff[3];
                                s2 ="";
                                s2+=buff[4];
                                s2+=buff[5];
                                s2+=buff[6];
                                s2+=buff[7];
                                s3 = "";
                                s3+=buff[8];
                                s3+=buff[9];
                                s3+=buff[10];
                                s3+=buff[11];
                                // cout<<"IN Server\n";
                                // cout<<s1<<" "<<s2<<"\n";
                                player2.x = stoi(s1);
                                player2.y = stoi(s2);
                                player2.lastStepDirection = stoi(s3);
                                if(buff[12]=='1'){
                                        player2.inMain = true;
                                }
                                else{
                                        player2.inMain = false;
                                }
                                if(buff[13]=='1'){
                                        player2.enterHostel = true;
                                }
                                else{
                                        player2.enterHostel = false;
                                }
                                if(buff[14]=='1'){
                                        player2.inLargeGround = true;
                                }
                                else{
                                        player2.inLargeGround = false;
                                }
                                if(buff[15]=='1'){
                                        player2.inTennisCourt = true;
                                }
                                else{
                                        player2.inTennisCourt = false;
                                }
                                if(buff[16]=='1'){
                                        player2.inVolleyCourt = true;
                                }
                                else{
                                        player2.inVolleyCourt = false;
                                }
                                if(buff[16]=='1'){
                                        player2.inVolleyCourt = true;
                                }
                                else{
                                        player2.inVolleyCourt = false;
                                }
                                if(buff[17]=='1'){
                                        player2.inLHC = true;
                                }
                                else{
                                        player2.inLHC = false;
                                }
                                if(buff[18]=='1'){
                                        player2.inLHC108 = true;
                                }
                                else{
                                        player2.inLHC108 = false;
                                }
                                if(buff[19]=='1'){
                                        player2.inLHC114 = true;
                                }
                                else{
                                        player2.inLHC114 = false;
                                }
                                if(buff[20]=='1'){
                                        player2.inLHC325 = true;
                                }
                                else{
                                        player2.inLHC325 = false;
                                }
                                if(buff[21]=='1'){
                                        player2.enterSAC = true;
                                }
                                else{
                                        player2.enterSAC = false;
                                }
                                if(buff[22]=='1'){
                                        player2.enterRestaurant = true;
                                }
                                else{
                                        player2.enterRestaurant = false;
                                }
                                if(buff[23]=='1'){
                                        player2.enterMasalaMix = true;
                                }
                                else{
                                        player2.enterMasalaMix = false;
                                }
                                if(buff[24]=='1'){
                                        player2.enterRajdhani = true;
                                }
                                else{
                                        player2.enterRajdhani = false;
                                }
                                if(buff[25]=='1'){
                                        player2.enterChaayos = true;
                                }
                                else{
                                        player2.enterChaayos = false;
                                }
                                if(buff[26]=='1'){
                                        player2.enterShiru = true;
                                }
                                else{
                                        player2.enterShiru = false;
                                }
                                if(buff[27]=='1'){
                                        player2.enterAmul = true;
                                }
                                else{
                                        player2.enterAmul = false;
                                }
                                if(buff[28]=='1'){
                                        player2.enterNescafe = true;
                                }
                                else{
                                        player2.enterNescafe = false;
                                }
                                if(buff[29]=='1'){
                                        player2.enterCCD = true;
                                }
                                else{
                                        player2.enterCCD = false;
                                }
                                if(buff[30]=='1'){
                                        player2.enterStaffCanteen = true;
                                }
                                else{
                                        player2.enterStaffCanteen = false;
                                }
                                if(buff[31]=='1'){
                                        player2.enterDilli16 = true;
                                }
                                else{
                                        player2.enterDilli16 = false;
                                }
                                if(buff[32]=='1'){
                                        player2.enterLibrary = true;
                                }
                                else{
                                        player2.enterLibrary = false;
                                }
                                if(buff[33]=='1'){
                                        player2.isSleeping = true;
                                }
                                else{
                                        player2.isSleeping = false;
                                }
                                if(buff[34]=='1'){
                                        player2.isStudying = true;
                                }
                                else{
                                        player2.isStudying = false;
                                }
            if(player1.inMain){    

                            if(insufficientMoney){
                                SDL_Rect insufficient = {1200,0,400,400};
                                SDL_RenderCopy(gRenderer,insufficientMoneyTex,NULL,&insufficient);
                             }
                            player1.incrementMoney();

                            
                                        // Nilgiri
                            SDL_Rect nilgiri = { SCREEN_WIDTH / 22, SCREEN_HEIGHT / 22, SCREEN_WIDTH / 10, SCREEN_HEIGHT / 10 };
                            

                            // SDL_SetTextInputRect(&fillRect);
                        
                            SDL_RenderCopy(gRenderer,nilgiriTex,NULL,&nilgiri);
                                        // SDL_RenderCopy(gRenderer,gTexture, NULL, NULL);

                           

                            // disptext(gRenderer, SCREEN_WIDTH / 22, SCREEN_HEIGHT / 22, SCREEN_WIDTH / 10, SCREEN_HEIGHT / 16, "Nilgiri",203, 230, 2) ;

                                        // Karakoram       

                            SDL_Rect karakoram = { SCREEN_WIDTH / 22 + 200, SCREEN_HEIGHT / 22,SCREEN_WIDTH / 10, SCREEN_HEIGHT / 10 };
                            

                            // SDL_SetTextInputRect(&fillRect);
                       
                            SDL_RenderCopy(gRenderer,karakoramTex,NULL,&karakoram);
                            SDL_DestroyTexture(imageTexture);            
                            // SDL_SetTextInputRect(&fillRect);
                       
                            
                            
                            // disptext(gRenderer, SCREEN_WIDTH / 22 + 200, SCREEN_HEIGHT / 22, SCREEN_WIDTH / 10, SCREEN_HEIGHT / 16, "Karakoram",203, 230, 2 ) ;
                            
                            
                            
                            
                            // Aravali
                            SDL_Rect aravali = { SCREEN_WIDTH / 22 + 400, SCREEN_HEIGHT / 22, SCREEN_WIDTH / 10, SCREEN_HEIGHT / 10 };

                            // SDL_SetTextInputRect(&fillRect);
                       
                            

                            // SDL_SetTextInputRect(&fillRect);
                       
                            SDL_RenderCopy(gRenderer,aravaliTex,NULL,&aravali);
                            SDL_DestroyTexture(imageTexture);            
                            
                            // disptext(gRenderer, SCREEN_WIDTH / 22 + 400, SCREEN_HEIGHT / 22, SCREEN_WIDTH / 10, SCREEN_HEIGHT / 16, "Aravali",203, 230, 2 ) ;
                            

                            // Jwala
                            SDL_Rect jwala = { SCREEN_WIDTH / 22 + 740, SCREEN_HEIGHT / 22, SCREEN_WIDTH / 10, SCREEN_HEIGHT / 10};
                            

                            // SDL_SetTextInputRect(&fillRect);
                       
                            SDL_RenderCopy(gRenderer,jwalaTex,NULL,&jwala);  
                            SDL_DestroyTexture(imageTexture);
                            
                            
                            // disptext(gRenderer, SCREEN_WIDTH / 22 + 800, SCREEN_HEIGHT / 22, SCREEN_WIDTH / 10, SCREEN_HEIGHT / 16, "Jwala",203, 230, 2 ) ;

                            // Kumaon
                            SDL_Rect kumaon = { SCREEN_WIDTH / 22 + 740, SCREEN_HEIGHT / 22+140, SCREEN_WIDTH / 10, SCREEN_HEIGHT / 10 };
                            

                            // SDL_SetTextInputRect(&fillRect);
                       
                            SDL_RenderCopy(gRenderer,kumaonTex,NULL,&kumaon);
                            SDL_DestroyTexture(imageTexture);

                            // SDL_SetTextInputRect(&fillRect);
                       

                            // disptext(gRenderer, SCREEN_WIDTH / 22 + 800, SCREEN_HEIGHT / 22 + 100, SCREEN_WIDTH / 10, SCREEN_HEIGHT / 16, "Kumaon",203, 230, 2 ) ;
                            
                            
                            // Vidyanchal
                            SDL_Rect vidyanchal = { SCREEN_WIDTH / 22 + 740, SCREEN_HEIGHT / 22+250, SCREEN_WIDTH / 10, SCREEN_HEIGHT / 10 };
                            

                            // SDL_SetTextInputRect(&fillRect);
                       
                            SDL_RenderCopy(gRenderer,vidyanchalTex,NULL,&vidyanchal);
                            SDL_DestroyTexture(imageTexture);


                            // disptext(gRenderer, SCREEN_WIDTH / 22 + 800, SCREEN_HEIGHT / 22 + 250, SCREEN_WIDTH / 10, SCREEN_HEIGHT / 16, "Vidyanchal",203, 230, 2 ) ;
                            
                             // Delhi - 16
                            SDL_Rect deli16 = { SCREEN_WIDTH / 22 + 400, SCREEN_HEIGHT / 22+135, SCREEN_WIDTH / 10, SCREEN_HEIGHT / 8 };
                             

                            // SDL_SetTextInputRect(&fillRect);
                       
                            SDL_RenderCopy(gRenderer,deli16Tex,NULL,&deli16);
                            
                            
                            // disptext(gRenderer, SCREEN_WIDTH / 22 + 400, SCREEN_HEIGHT / 22 + 120, SCREEN_WIDTH / 10, SCREEN_HEIGHT / 16, "Dilli-16" ,255, 255, 255) ;

                            // Tennis Court

                            SDL_Rect tennisCourt = { SCREEN_WIDTH / 22 + 200, SCREEN_HEIGHT / 22+200, SCREEN_WIDTH / 8, SCREEN_HEIGHT / 12 };
                            
                            SDL_RenderCopy(gRenderer,tennisCourtTex,NULL,&tennisCourt);
                            SDL_DestroyTexture(imageTexture);
                       
                            
                            
                            
                            
                            
                            // Volley Ball Court
                                SDL_Rect volleyBallCourt = { SCREEN_WIDTH / 22 + 350, SCREEN_HEIGHT / 22+195, SCREEN_WIDTH / 8, SCREEN_HEIGHT / 10};
                            
                            SDL_RenderCopy(gRenderer,volleyBallCourtTex,NULL,&volleyBallCourt);
                            SDL_DestroyTexture(imageTexture);

                            // SDL_SetTextInputRect(&fillRect);
                       
                            
                            
                            
                            
                            
                            

                            // Shivalik

                            SDL_Rect shivalik = { SCREEN_WIDTH / 22 + 365, SCREEN_HEIGHT / 22+290, SCREEN_WIDTH / 10, SCREEN_HEIGHT / 10 };
                            
                            // SDL_SetTextInputRect(&fillRect);
                       
                            SDL_RenderCopy(gRenderer,shivalikTex,NULL,&shivalik);
                            SDL_DestroyTexture(imageTexture);
                            
                            
                            
                            

                            // Zanskar

                            SDL_Rect zanskar = { SCREEN_WIDTH / 22 + 240, SCREEN_HEIGHT / 22+290, SCREEN_WIDTH / 10, SCREEN_HEIGHT / 10 };
                            

                            // SDL_SetTextInputRect(&fillRect);
                       
                            SDL_RenderCopy(gRenderer,zanskarTex,NULL,&zanskar); 
                            SDL_DestroyTexture(imageTexture);          

                            
                            // disptext(gRenderer, SCREEN_WIDTH / 22 + 200, SCREEN_HEIGHT / 22+300, SCREEN_WIDTH / 10, SCREEN_HEIGHT / 16, "Zanskar",203, 230, 2 ) ;
                            

                            // SAC

                            SDL_Rect sac = { 0, SCREEN_HEIGHT / 22+220, SCREEN_WIDTH / 10, SCREEN_HEIGHT / 8 };

                       
                            SDL_RenderCopy(gRenderer,sacTex,NULL,&sac); 
                            SDL_DestroyTexture(imageTexture);
                            
                            
                            // disptext(gRenderer, SCREEN_WIDTH / 22, SCREEN_HEIGHT / 22+270, SCREEN_WIDTH / 16, SCREEN_HEIGHT / 10, "SAC",255,255,255 ) ;



                                        // Masala Mix
                            SDL_Rect masalaMix = { SCREEN_WIDTH / 22+230,  SCREEN_HEIGHT / 22+300+SCREEN_HEIGHT / 16, SCREEN_WIDTH / 12, SCREEN_HEIGHT / 8 };
                             

                            SDL_RenderCopy(gRenderer,masalaMixTex,NULL,&masalaMix);
                            SDL_DestroyTexture(imageTexture);
                            
                            
                            
                            // disptext(gRenderer,  SCREEN_WIDTH / 22+200,  SCREEN_HEIGHT / 22+310+SCREEN_HEIGHT / 16, SCREEN_WIDTH / 12, SCREEN_HEIGHT / 16, "Masala Mix",252, 186, 3 ) ;



                            // Rajdhani
                                        SDL_Rect rajdhani = { SCREEN_WIDTH / 22+200+SCREEN_WIDTH / 12,SCREEN_HEIGHT / 22+310+SCREEN_HEIGHT / 16, SCREEN_WIDTH / 12, SCREEN_HEIGHT / 12 };
                            
                            SDL_RenderCopy(gRenderer,rajdhaniTex,NULL,&rajdhani);
                            SDL_DestroyTexture(imageTexture);
                            
                            
                            // disptext(gRenderer,  SCREEN_WIDTH / 22+210+SCREEN_WIDTH / 12,SCREEN_HEIGHT / 22+310+SCREEN_HEIGHT / 16, SCREEN_WIDTH / 12, SCREEN_HEIGHT / 16 , "Rajdhani",255,255,255 ) ;
                            
                            

                            // Chaayos
                            SDL_Rect chaayos = { SCREEN_WIDTH / 22+200+2*SCREEN_WIDTH / 12, SCREEN_HEIGHT / 22+320+SCREEN_HEIGHT / 16, SCREEN_WIDTH / 14, SCREEN_HEIGHT / 14 };
                            SDL_RenderCopy(gRenderer,chaayosTex,NULL,&chaayos);
                            SDL_DestroyTexture(imageTexture);
                            
                            
                            // disptext(gRenderer,  SCREEN_WIDTH / 22+220+2*SCREEN_WIDTH / 12, SCREEN_HEIGHT / 22+310+SCREEN_HEIGHT / 16, SCREEN_WIDTH / 12, SCREEN_HEIGHT / 16, "Chaayos",255,255,255 ) ;
                            
                            

                            // IIT-D Hospital
                                        SDL_Rect hospital = {  SCREEN_WIDTH / 22+200, SCREEN_HEIGHT / 22+410+SCREEN_HEIGHT / 16, SCREEN_WIDTH / 6, SCREEN_HEIGHT / 8 };
                            SDL_SetRenderDrawColor( gRenderer, 255, 0, 0, 0xFF ); 
                            
                            SDL_RenderCopy(gRenderer,hospitalTex,NULL,&hospital);
                            SDL_DestroyTexture(imageTexture);


                                


                            // Bharti - School of AI
                            SDL_Rect bharti = {  SCREEN_WIDTH / 22+200 , SCREEN_HEIGHT / 22+430+SCREEN_HEIGHT / 16+  SCREEN_HEIGHT / 10, SCREEN_WIDTH / 6, SCREEN_HEIGHT / 8 };
                            
                            SDL_RenderCopy(gRenderer,bhartiTex,NULL,&bharti);
                            SDL_DestroyTexture(imageTexture);
                            // SDL_SetRenderDrawColor( gRenderer, 164, 191, 31, 0xFF ); 

                            // SDL_RenderFillRect( gRenderer, &bharti );
                            
                            // disptext(gRenderer,  SCREEN_WIDTH / 22+200 , SCREEN_HEIGHT / 22+430+SCREEN_HEIGHT / 16+  SCREEN_HEIGHT / 10, SCREEN_WIDTH / 8, SCREEN_HEIGHT / 10 , "Bharti Building",255,255,255 ) ;
                // 
                            // Large ground 

                            SDL_Rect largeGround = {  SCREEN_WIDTH / 22 , SCREEN_HEIGHT / 22+450, SCREEN_WIDTH /12, SCREEN_HEIGHT / 6 };
                            
                            SDL_RenderCopy(gRenderer,largeGroundTex,NULL,&largeGround);
                            SDL_DestroyTexture(imageTexture);

                            SDL_Rect gtree1 = {8 , SCREEN_HEIGHT / 22+400, 100,100};
                            
                            SDL_RenderCopy(gRenderer,gtree1Tex,NULL,&gtree1);  
                            SDL_DestroyTexture(imageTexture); 


                            SDL_Rect gtree2 = {8 , SCREEN_HEIGHT / 22+400+30, 100,100};
                            
                            SDL_RenderCopy(gRenderer,gtree2Tex,NULL,&gtree2); 
                            SDL_DestroyTexture(imageTexture);


                            SDL_Rect gtree3 = {8 , SCREEN_HEIGHT / 22+400+60, 100,100};
                            
                            SDL_RenderCopy(gRenderer,gtree3Tex,NULL,&gtree3); 
                            SDL_DestroyTexture(imageTexture);

                            SDL_Rect gtree4 = {8 , SCREEN_HEIGHT / 22+400+90, 100,100};
                            SDL_RenderCopy(gRenderer,gtree4Tex,NULL,&gtree4); 
                            SDL_DestroyTexture(imageTexture);

                            SDL_Rect gtree5 = {8 , SCREEN_HEIGHT / 22+400+120, 100,100};
                            SDL_RenderCopy(gRenderer,gtree5Tex,NULL,&gtree5);   
                            SDL_DestroyTexture(imageTexture);


                            SDL_Rect gtree6 = {8 , SCREEN_HEIGHT / 22+400+150, 100,100};
                            SDL_RenderCopy(gRenderer,gtree6Tex,NULL,&gtree6); 
                            SDL_DestroyTexture(imageTexture);


                            SDL_Rect gtree7 = {8+SCREEN_WIDTH /12+22 , SCREEN_HEIGHT / 22+400, 100,100};
                            SDL_RenderCopy(gRenderer,gtree7Tex,NULL,&gtree7);  
                            SDL_DestroyTexture(imageTexture); 


                            SDL_Rect gtree8 = {8+SCREEN_WIDTH /12+22 , SCREEN_HEIGHT / 22+400+30, 100,100};
                            // loadFromFile("tree-top.png");
                            SDL_RenderCopy(gRenderer,gtree8Tex,NULL,&gtree8); 
                            SDL_DestroyTexture(imageTexture);


                            SDL_Rect gtree9 = {8+SCREEN_WIDTH /12+22 , SCREEN_HEIGHT / 22+400+60, 100,100};
                            // loadFromFile("tree-top.png");
                            SDL_RenderCopy(gRenderer,gtree9Tex,NULL,&gtree9); 
                            SDL_DestroyTexture(imageTexture);

                            SDL_Rect gtree10 = {8+SCREEN_WIDTH /12+22 , SCREEN_HEIGHT / 22+400+90, 100,100};
                            // loadFromFile("tree-top.png");
                            SDL_RenderCopy(gRenderer,gtree10Tex,NULL,&gtree10); 
                            SDL_DestroyTexture(imageTexture);

                            SDL_Rect gtree11 = {8+SCREEN_WIDTH /12+22 , SCREEN_HEIGHT / 22+400+120, 100,100};
                            // loadFromFile("tree-top.png");
                            SDL_RenderCopy(gRenderer,gtree11Tex,NULL,&gtree11); 
                            SDL_DestroyTexture(imageTexture);  


                            SDL_Rect gtree12 = {8+SCREEN_WIDTH /12+22 , SCREEN_HEIGHT / 22+400+150, 100,100};
                            // loadFromFile("tree-top.png");
                            SDL_RenderCopy(gRenderer,gtree12Tex,NULL,&gtree12);
                            SDL_DestroyTexture(imageTexture); 


                            // SDL_SetRenderDrawColor( gRenderer, 92, 8, 8, 0xFF ); 

                            // SDL_RenderFillRect( gRenderer, &largeGround );
                            
                            
                            
                            // disptext(gRenderer,  SCREEN_WIDTH / 22 , SCREEN_HEIGHT / 22+450, SCREEN_WIDTH / 10, SCREEN_HEIGHT / 4 , "Large Ground",255,255,255 ) ;

                            // Staff canteen

                            SDL_Rect staffCanteen = {  SCREEN_WIDTH / 22 , SCREEN_HEIGHT / 22+470 + SCREEN_HEIGHT / 4, SCREEN_WIDTH / 10, SCREEN_HEIGHT / 10 };
                            SDL_RenderCopy(gRenderer,staffCanteenTex,NULL,&staffCanteen);
                            SDL_DestroyTexture(imageTexture);
                            
                            
                            // disptext(gRenderer,  SCREEN_WIDTH / 22 , SCREEN_HEIGHT / 22+470 + SCREEN_HEIGHT / 4, SCREEN_WIDTH / 16, SCREEN_HEIGHT / 16  , "Staff Canteen",255,255,255 ) ;


                            // LHC

                            SDL_Rect LHC = {  SCREEN_WIDTH / 22 , SCREEN_HEIGHT / 22+490 + SCREEN_HEIGHT / 4 +  SCREEN_HEIGHT / 16, SCREEN_WIDTH / 10, SCREEN_HEIGHT / 10 };
                            SDL_RenderCopy(gRenderer,LHCTex,NULL,&LHC);
                            SDL_DestroyTexture(imageTexture);

                            // SDL_RenderFillRect( gRenderer, &LHC);
                            
                            // dogra hall

                            SDL_Rect dograHall = {  SCREEN_WIDTH / 22+260 , SCREEN_HEIGHT / 22+490 + SCREEN_HEIGHT / 4 +  SCREEN_HEIGHT / 16, SCREEN_WIDTH / 8, SCREEN_HEIGHT / 8 };
                            SDL_RenderCopy(gRenderer,dograHallTex,NULL,&dograHall);
                            SDL_DestroyTexture(imageTexture);

                            // csc

                            SDL_Rect csc ={ SCREEN_WIDTH / 22+300+5*SCREEN_WIDTH / 12, SCREEN_HEIGHT / 22+520 + SCREEN_HEIGHT / 4+ SCREEN_HEIGHT / 16+40, SCREEN_WIDTH / 10, SCREEN_HEIGHT / 8 };
                            SDL_RenderCopy(gRenderer,cscTex,NULL,&csc);
                            SDL_DestroyTexture(imageTexture);
                            
                            // disptext(gRenderer,  SCREEN_WIDTH / 22 , SCREEN_HEIGHT / 22+490 + SCREEN_HEIGHT / 4 +  SCREEN_HEIGHT / 16, SCREEN_WIDTH / 10, SCREEN_HEIGHT / 10  , "LHC",255,255,255 ) ;



                            // Satpura

                            SDL_Rect satpura ={ SCREEN_WIDTH / 22+230+3*SCREEN_WIDTH / 12, SCREEN_HEIGHT / 22+310+SCREEN_HEIGHT / 16+40, SCREEN_WIDTH / 10, SCREEN_HEIGHT / 10 };
                            SDL_RenderCopy(gRenderer,satpuraTex,NULL,&satpura); 
                            SDL_DestroyTexture(imageTexture);


                            // girnar

                            SDL_Rect girnar={ SCREEN_WIDTH / 22+160+3*SCREEN_WIDTH / 12, SCREEN_HEIGHT / 22+310+SCREEN_HEIGHT / 16+140, SCREEN_WIDTH / 10, SCREEN_HEIGHT / 10 };
                            // SDL_SetTextInputRect(&fillRect);
                       
                            SDL_RenderCopy(gRenderer,girnarTex,NULL,&girnar); 
                            SDL_DestroyTexture(imageTexture);

                            // udaigiri

                            SDL_Rect udaigiri={ SCREEN_WIDTH / 22+160+3*SCREEN_WIDTH / 12, SCREEN_HEIGHT / 22+310+SCREEN_HEIGHT / 16+110+SCREEN_HEIGHT / 10, SCREEN_WIDTH / 10, SCREEN_HEIGHT / 10 };
                            // SDL_SetTextInputRect(&fillRect);
                       
                            SDL_RenderCopy(gRenderer,udaigiriTex,NULL,&udaigiri);
                            SDL_DestroyTexture(imageTexture); 


                            
                            
                            // disptext(gRenderer,  SCREEN_WIDTH / 22+230+3*SCREEN_WIDTH / 12, SCREEN_HEIGHT / 22+310+SCREEN_HEIGHT / 16+40, SCREEN_WIDTH / 10, SCREEN_HEIGHT / 16  , "Satpura",203, 230, 2  ) ;



                            // Shiru's cafe

                            SDL_Rect shiru ={ SCREEN_WIDTH / 22+220+2*SCREEN_WIDTH / 12, SCREEN_HEIGHT / 22+470 + SCREEN_HEIGHT / 4, SCREEN_WIDTH / 10, SCREEN_HEIGHT / 10 };
                            SDL_RenderCopy(gRenderer,shiruTex,NULL,&shiru);
                            SDL_DestroyTexture(imageTexture);
                            
                            
                            // disptext(gRenderer,  SCREEN_WIDTH / 22+220+2*SCREEN_WIDTH / 12, SCREEN_HEIGHT / 22+470 + SCREEN_HEIGHT / 4, SCREEN_WIDTH / 12, SCREEN_HEIGHT / 16  , "Shiru's Cafe",163, 163, 162 ) ;
                            
                            

                            // Amul
                            SDL_Rect amul ={ SCREEN_WIDTH / 22+230+3*SCREEN_WIDTH / 12, SCREEN_HEIGHT / 22+470 + SCREEN_HEIGHT / 4, SCREEN_WIDTH / 10, SCREEN_HEIGHT / 10 };

                            SDL_RenderCopy(gRenderer,amulTex,NULL,&amul);
                            SDL_DestroyTexture(imageTexture);
                            
                                            

                            // Nescafe
                            SDL_Rect nescafe ={ SCREEN_WIDTH / 22+260+4*SCREEN_WIDTH / 12, SCREEN_HEIGHT / 22+420 + SCREEN_HEIGHT / 4, SCREEN_WIDTH / 9, SCREEN_HEIGHT / 4 };
                            SDL_RenderCopy(gRenderer,nescafeTex,NULL,&nescafe);
                            SDL_DestroyTexture(imageTexture);        
                            


                            // CCD 


                            SDL_Rect ccd ={ SCREEN_WIDTH / 22+300+5*SCREEN_WIDTH / 12, SCREEN_HEIGHT / 22+500 + SCREEN_HEIGHT / 4, SCREEN_WIDTH / 8, SCREEN_HEIGHT / 6 };
                            SDL_RenderCopy(gRenderer,ccdTex,NULL,&ccd);
                            SDL_DestroyTexture(imageTexture);
                            
                            
                        
                            
                            // central library

                            SDL_Rect clibrary = {SCREEN_WIDTH / 22+220+2*SCREEN_WIDTH / 12, SCREEN_HEIGHT / 22+500 + SCREEN_HEIGHT / 4+ SCREEN_HEIGHT / 16, SCREEN_WIDTH / 6, SCREEN_HEIGHT / 12 +80};
                            SDL_RenderCopy(gRenderer,clibraryTex,NULL,&clibrary);
                            SDL_DestroyTexture(imageTexture);

                            // Main building

                            SDL_Rect mainBuilding ={  SCREEN_WIDTH / 22+850+2*SCREEN_WIDTH / 12, SCREEN_HEIGHT / 22+500 + SCREEN_HEIGHT / 4+ SCREEN_HEIGHT / 16, SCREEN_WIDTH / 6, SCREEN_HEIGHT / 12 +80};
                            SDL_RenderCopy(gRenderer,mainBuildingTex,NULL,&mainBuilding);
                            SDL_DestroyTexture(imageTexture);
                            // SDL_SetRenderDrawColor( gRenderer,164, 191, 31, 0xFF ); 
                            // SDL_RenderFillRect( gRenderer, &mainBuilding); 


                            
                            // disptext(gRenderer,  SCREEN_WIDTH / 22+220+2*SCREEN_WIDTH / 12, SCREEN_HEIGHT / 22+540 + SCREEN_HEIGHT / 4+ SCREEN_HEIGHT / 16+40, SCREEN_WIDTH / 4, SCREEN_HEIGHT / 12 , "Main Building",255,255,255 ) ;

                            // ROADS

                            // SAC CIRCLE ROAD
                            SDL_Rect sacCircle ={  SCREEN_WIDTH / 22+70,SCREEN_HEIGHT / 22+200, SCREEN_WIDTH / 5, SCREEN_HEIGHT / 5};
                            SDL_RenderCopy(gRenderer,sacCircleTex,NULL,&sacCircle);
                            SDL_DestroyTexture(imageTexture);

                            SDL_Rect vr1 ={  SCREEN_WIDTH / 22+70,SCREEN_HEIGHT / 22+290, SCREEN_WIDTH / 5, SCREEN_HEIGHT / 5};
                            SDL_RenderCopy(gRenderer,vrTex,NULL,&vr1);
                            SDL_DestroyTexture(imageTexture);

                            SDL_Rect vr1dash ={  SCREEN_WIDTH / 22+67,SCREEN_HEIGHT / 22+30, SCREEN_WIDTH / 5, SCREEN_HEIGHT / 5};
                            SDL_RenderCopy(gRenderer,vrTex,NULL,&vr1dash);
                            SDL_DestroyTexture(imageTexture);

                            SDL_Rect vr2 ={  SCREEN_WIDTH / 22+70,SCREEN_HEIGHT / 22+380, SCREEN_WIDTH / 5, SCREEN_HEIGHT / 5};
                            SDL_RenderCopy(gRenderer,vrTex,NULL,&vr2);
                            SDL_DestroyTexture(imageTexture);

                            SDL_Rect vr3 ={  SCREEN_WIDTH / 22+70,SCREEN_HEIGHT / 22+470, SCREEN_WIDTH / 5, SCREEN_HEIGHT / 5};
                            SDL_RenderCopy(gRenderer,vrTex,NULL,&vr3);
                            SDL_DestroyTexture(imageTexture);
                                

                            SDL_Rect vr4 ={  SCREEN_WIDTH / 22+70,SCREEN_HEIGHT / 22+560, SCREEN_WIDTH / 5, SCREEN_HEIGHT / 5};
                            SDL_RenderCopy(gRenderer,vrTex,NULL,&vr4);
                            SDL_DestroyTexture(imageTexture);

                            SDL_Rect vr5 ={  SCREEN_WIDTH / 22+70,SCREEN_HEIGHT / 22+650, SCREEN_WIDTH / 5, SCREEN_HEIGHT / 5};
                            SDL_RenderCopy(gRenderer,vrTex,NULL,&vr5);
                            SDL_DestroyTexture(imageTexture);

                            SDL_Rect vr6 ={  SCREEN_WIDTH / 22+70,SCREEN_HEIGHT / 22+710, SCREEN_WIDTH / 5, SCREEN_HEIGHT / 4};
                            SDL_RenderCopy(gRenderer,vrTex,NULL,&vr6);
                            SDL_DestroyTexture(imageTexture);



                            // SDL_Rect vr6 ={  SCREEN_WIDTH / 22+70,SCREEN_HEIGHT / 22+110, SCREEN_WIDTH / 5, SCREEN_HEIGHT / 5};
                            // loadFromFile("verticalroad2.png");
                            // SDL_RenderCopy(gRenderer,imageTexture,NULL,&vr6);

                        
                            SDL_Rect tp1 ={  SCREEN_WIDTH / 22+70,SCREEN_HEIGHT / 22+96, SCREEN_WIDTH / 5, SCREEN_HEIGHT / 5};
                            SDL_RenderCopy(gRenderer,tpTex,NULL,&tp1);  
                            SDL_DestroyTexture(imageTexture);      


                            SDL_Rect hr1 = {SCREEN_WIDTH / 22+350,SCREEN_HEIGHT / 22+96, SCREEN_WIDTH / 5, SCREEN_HEIGHT / 5};

                            SDL_RenderCopy(gRenderer,hr1Tex,NULL,&hr1);
                            SDL_DestroyTexture(imageTexture);

                            SDL_Rect hr1dash = {SCREEN_WIDTH / 22+48,SCREEN_HEIGHT / 22+96, SCREEN_WIDTH / 5, SCREEN_HEIGHT / 5};

                            SDL_RenderCopy(gRenderer,hr1Tex,NULL,&hr1dash);
                            SDL_DestroyTexture(imageTexture);

                            SDL_Rect hr2 = {SCREEN_WIDTH / 22+350+SCREEN_WIDTH / 5,SCREEN_HEIGHT / 22+96, SCREEN_WIDTH / 5, SCREEN_HEIGHT / 5};

                            SDL_RenderCopy(gRenderer,hr1Tex,NULL,&hr2);
                            SDL_DestroyTexture(imageTexture);


                            SDL_Rect hr3 = {SCREEN_WIDTH / 22-100,SCREEN_HEIGHT / 22+96, SCREEN_WIDTH / 5, SCREEN_HEIGHT / 5};

                            SDL_RenderCopy(gRenderer,hr1Tex,NULL,&hr3);
                            SDL_DestroyTexture(imageTexture);


                            SDL_Rect hr4 = {SCREEN_WIDTH / 22+150,SCREEN_HEIGHT / 22+200, SCREEN_WIDTH / 5, SCREEN_HEIGHT / 5};

                            SDL_RenderCopy(gRenderer,hr2Tex,NULL,&hr4);
                            SDL_DestroyTexture(imageTexture);


                            SDL_Rect hr5 = {SCREEN_WIDTH / 22+150+95,SCREEN_HEIGHT / 22+200, SCREEN_WIDTH / 5, SCREEN_HEIGHT / 5};

                            SDL_RenderCopy(gRenderer,hr2Tex,NULL,&hr5);
                            SDL_DestroyTexture(imageTexture);

                            SDL_Rect hr6 = {SCREEN_WIDTH / 22+150+95+95,SCREEN_HEIGHT / 22+200, SCREEN_WIDTH / 5, SCREEN_HEIGHT / 5};

                            SDL_RenderCopy(gRenderer,hr2Tex,NULL,&hr6);
                            SDL_DestroyTexture(imageTexture);


                            SDL_Rect hr7 = {SCREEN_WIDTH / 22+150+95+95+95,SCREEN_HEIGHT / 22+200, SCREEN_WIDTH / 5, SCREEN_HEIGHT / 5};

                            SDL_RenderCopy(gRenderer,hr2Tex,NULL,&hr7);
                            SDL_DestroyTexture(imageTexture);



                            SDL_Rect hr8 = {SCREEN_WIDTH / 22+150,SCREEN_HEIGHT / 22+200+430, SCREEN_WIDTH / 5, SCREEN_HEIGHT / 5};

                            SDL_RenderCopy(gRenderer,hr2Tex,NULL,&hr8);
                            SDL_DestroyTexture(imageTexture);

                            SDL_Rect hr9 = {SCREEN_WIDTH / 22+150+95,SCREEN_HEIGHT / 22+200+430, SCREEN_WIDTH / 5, SCREEN_HEIGHT / 5};

                            SDL_RenderCopy(gRenderer,hr2Tex,NULL,&hr9);
                            SDL_DestroyTexture(imageTexture);


                            SDL_Rect hr10 = {SCREEN_WIDTH / 22+150+95+95,SCREEN_HEIGHT / 22+200+430, SCREEN_WIDTH / 5, SCREEN_HEIGHT / 5};

                            // loadFromFile("horizontalroad2.png");
                            SDL_RenderCopy(gRenderer,hr2Tex,NULL,&hr10);
                            SDL_DestroyTexture(imageTexture);

                            SDL_Rect hr11 = {SCREEN_WIDTH / 22+150+95+95+95,SCREEN_HEIGHT / 22+200+430, SCREEN_WIDTH / 5, SCREEN_HEIGHT / 5};

                            // loadFromFile("horizontalroad2.png");
                            SDL_RenderCopy(gRenderer,hr2Tex,NULL,&hr11);
                            SDL_DestroyTexture(imageTexture);

                            SDL_Rect hr12 = {SCREEN_WIDTH / 22+50,SCREEN_HEIGHT / 22+200+430, SCREEN_WIDTH / 5, SCREEN_HEIGHT / 5};

                            // loadFromFile("horizontalroad2.png");
                            SDL_RenderCopy(gRenderer,hr2Tex,NULL,&hr12);
                            SDL_DestroyTexture(imageTexture);

                            SDL_Rect hr13 = {SCREEN_WIDTH / 22+10,SCREEN_HEIGHT / 22+200+430, SCREEN_WIDTH / 5, SCREEN_HEIGHT / 5};

                            // loadFromFile("horizontalroad2.png");
                            SDL_RenderCopy(gRenderer,hr2Tex,NULL,&hr13);
                            SDL_DestroyTexture(imageTexture);

                            SDL_Rect hr14 = {SCREEN_WIDTH / 22+150+95+95+95+95,SCREEN_HEIGHT / 22+200+430, SCREEN_WIDTH / 5, SCREEN_HEIGHT / 5};

                            // loadFromFile("horizontalroad2.png");
                            SDL_RenderCopy(gRenderer,hr2Tex,NULL,&hr14);
                            SDL_DestroyTexture(imageTexture);

                            SDL_Rect hr15 = {SCREEN_WIDTH / 22+150+95+95+95+95,SCREEN_HEIGHT / 22+200+430, SCREEN_WIDTH / 5, SCREEN_HEIGHT / 5};

                            // loadFromFile("horizontalroad2.png");
                            SDL_RenderCopy(gRenderer,hr2Tex,NULL,&hr15);
                            SDL_DestroyTexture(imageTexture);


                            SDL_Rect hr16 = {SCREEN_WIDTH / 22+150+95+95+95+95+95,SCREEN_HEIGHT / 22+200+430, SCREEN_WIDTH / 5, SCREEN_HEIGHT / 5};

                            // loadFromFile("horizontalroad2.png");
                            SDL_RenderCopy(gRenderer,hr2Tex,NULL,&hr16);
                            SDL_DestroyTexture(imageTexture);

                            SDL_Rect hr17 = {SCREEN_WIDTH / 22,SCREEN_HEIGHT / 22+200+430+240, SCREEN_WIDTH / 5, SCREEN_HEIGHT / 5};

                            // loadFromFile("horizontalroad2.png");
                            SDL_RenderCopy(gRenderer,hr2Tex,NULL,&hr17);
                            SDL_DestroyTexture(imageTexture);


                            SDL_Rect hr18 = {SCREEN_WIDTH / 22+95,SCREEN_HEIGHT / 22+200+430+240, SCREEN_WIDTH / 5, SCREEN_HEIGHT / 5};

                            // loadFromFile("horizontalroad2.png");
                            SDL_RenderCopy(gRenderer,hr2Tex,NULL,&hr18);
                            SDL_DestroyTexture(imageTexture);


                            SDL_Rect hr19 = {SCREEN_WIDTH / 22+190,SCREEN_HEIGHT / 22+200+430+240, SCREEN_WIDTH / 5, SCREEN_HEIGHT / 5};

                            // loadFromFile("horizontalroad2.png");
                            SDL_RenderCopy(gRenderer,hr2Tex,NULL,&hr19);
                            SDL_DestroyTexture(imageTexture);


                            SDL_Rect hr20 = {SCREEN_WIDTH / 22+285,SCREEN_HEIGHT / 22+200+430+240, SCREEN_WIDTH / 5, SCREEN_HEIGHT / 5};

                            // loadFromFile("horizontalroad2.png");
                            SDL_RenderCopy(gRenderer,hr2Tex,NULL,&hr20);
                            SDL_DestroyTexture(imageTexture);


                            SDL_Rect hr21 = {SCREEN_WIDTH / 22+370,SCREEN_HEIGHT / 22+200+430+240, SCREEN_WIDTH / 5, SCREEN_HEIGHT / 5};

                            // loadFromFile("horizontalroad2.png");
                            SDL_RenderCopy(gRenderer,hr2Tex,NULL,&hr21);
                            SDL_DestroyTexture(imageTexture);

                            SDL_Rect hr22 = {SCREEN_WIDTH / 22+465,SCREEN_HEIGHT / 22+200+430+240, SCREEN_WIDTH / 5, SCREEN_HEIGHT / 5};

                            // loadFromFile("horizontalroad2.png");
                            SDL_RenderCopy(gRenderer,hr2Tex,NULL,&hr22);
                            SDL_DestroyTexture(imageTexture);


                            SDL_Rect hr23 = {SCREEN_WIDTH / 22+560,SCREEN_HEIGHT / 22+200+430+240, SCREEN_WIDTH / 5, SCREEN_HEIGHT / 5};

                            // loadFromFile("horizontalroad2.png");
                            SDL_RenderCopy(gRenderer,hr2Tex,NULL,&hr23);
                            SDL_DestroyTexture(imageTexture);

                            SDL_Rect hr24 = {SCREEN_WIDTH / 22+655,SCREEN_HEIGHT / 22+200+430+240, SCREEN_WIDTH / 5, SCREEN_HEIGHT / 5};

                            // loadFromFile("horizontalroad2.png");
                            SDL_RenderCopy(gRenderer,hr2Tex,NULL,&hr24);
                            SDL_DestroyTexture(imageTexture);


                            SDL_Rect vr7 = {SCREEN_WIDTH / 22+150+95+95+95+95+95+180,SCREEN_HEIGHT / 22+200+393, SCREEN_WIDTH / 5, SCREEN_HEIGHT / 5};

                            SDL_RenderCopy(gRenderer,vrTex,NULL,&vr7);
                            SDL_DestroyTexture(imageTexture);


                            SDL_Rect vr8 = {SCREEN_WIDTH / 22+150+95+95+95+95+95+180,SCREEN_HEIGHT / 22+200+393+80, SCREEN_WIDTH / 5, SCREEN_HEIGHT / 5};

                            // loadFromFile("verticalroad.png");
                            SDL_RenderCopy(gRenderer,vrTex,NULL,&vr8);
                            SDL_DestroyTexture(imageTexture);


                            SDL_Rect vr9 = {SCREEN_WIDTH / 22+150+95+95+95+95+95+180,SCREEN_HEIGHT / 22+200+393+80+80, SCREEN_WIDTH / 5, SCREEN_HEIGHT / 5};

                            // loadFromFile("verticalroad.png");
                            SDL_RenderCopy(gRenderer,vrTex,NULL,&vr9);
                            SDL_DestroyTexture(imageTexture);

                            SDL_Rect vr10 = {SCREEN_WIDTH / 22+150+95+95+79+180,SCREEN_HEIGHT / 22+170, SCREEN_WIDTH / 5, SCREEN_HEIGHT / 5};

                            // loadFromFile("verticalroad.png");
                            SDL_RenderCopy(gRenderer,vrTex,NULL,&vr10);
                            SDL_DestroyTexture(imageTexture);


                            SDL_Rect vr11 = {SCREEN_WIDTH / 22+150+95+95+79+180,SCREEN_HEIGHT / 22+170+70, SCREEN_WIDTH / 5, SCREEN_HEIGHT / 5};

                            // loadFromFile("verticalroad.png");
                            SDL_RenderCopy(gRenderer,vrTex,NULL,&vr11);
                            SDL_DestroyTexture(imageTexture);


                            SDL_Rect vr12 = {SCREEN_WIDTH / 22+150+80+79+180,SCREEN_HEIGHT / 22+170, SCREEN_WIDTH / 5, SCREEN_HEIGHT / 5};

                            // loadFromFile("verticalroad.png");
                            SDL_RenderCopy(gRenderer,vrTex,NULL,&vr12);
                            SDL_DestroyTexture(imageTexture);


                            SDL_Rect vr13 = {SCREEN_WIDTH / 22+150+80+79+180,SCREEN_HEIGHT / 22+170+80, SCREEN_WIDTH / 5, SCREEN_HEIGHT / 5};

                            // loadFromFile("verticalroad.png");
                            SDL_RenderCopy(gRenderer,vrTex,NULL,&vr13);
                            SDL_DestroyTexture(imageTexture);



                            SDL_Rect vr14 = {SCREEN_WIDTH / 22+150+80+79+180,SCREEN_HEIGHT / 22+170+80+80, SCREEN_WIDTH / 5, SCREEN_HEIGHT / 5};

                            // loadFromFile("verticalroad.png");
                            SDL_RenderCopy(gRenderer,vrTex,NULL,&vr14);
                            SDL_DestroyTexture(imageTexture);


                            SDL_Rect vr15 = {SCREEN_WIDTH / 22+150+95+95+79+180,SCREEN_HEIGHT / 22+40, SCREEN_WIDTH / 5, SCREEN_HEIGHT / 5};

                            // loadFromFile("verticalroad.png");
                            SDL_RenderCopy(gRenderer,vrTex,NULL,&vr15);
                            SDL_DestroyTexture(imageTexture);



                            SDL_Rect vr16 = {SCREEN_WIDTH / 22+150+95+95+79+180,SCREEN_HEIGHT / 22+80, SCREEN_WIDTH / 5, SCREEN_HEIGHT / 5};

                            // loadFromFile("verticalroad.png");
                            SDL_RenderCopy(gRenderer,vrTex,NULL,&vr16);
                            SDL_DestroyTexture(imageTexture);


                            



                            SDL_Rect hr26 = {SCREEN_WIDTH / 22+150+175,SCREEN_HEIGHT / 22+370, SCREEN_WIDTH / 5, SCREEN_HEIGHT / 5};

                            // loadFromFile("horizontalroad2.png");
                            SDL_RenderCopy(gRenderer,hr2Tex,NULL,&hr26);
                            SDL_DestroyTexture(imageTexture);


                            SDL_Rect hr27 = {SCREEN_WIDTH / 22+150+80,SCREEN_HEIGHT / 22+370, SCREEN_WIDTH / 5, SCREEN_HEIGHT / 5};

                            // loadFromFile("horizontalroad2.png");
                            SDL_RenderCopy(gRenderer,hr2Tex,NULL,&hr27);
                            SDL_DestroyTexture(imageTexture);

                            SDL_Rect hr28 = {SCREEN_WIDTH / 22+135,SCREEN_HEIGHT / 22+370, SCREEN_WIDTH / 5, SCREEN_HEIGHT / 5};

                            // loadFromFile("horizontalroad2.png");
                            SDL_RenderCopy(gRenderer,hr2Tex,NULL,&hr28);
                            SDL_DestroyTexture(imageTexture);

                            SDL_Rect hr29 = {SCREEN_WIDTH / 22+40,SCREEN_HEIGHT / 22+370, SCREEN_WIDTH / 5, SCREEN_HEIGHT / 5};

                            // loadFromFile("horizontalroad2.png");
                            SDL_RenderCopy(gRenderer,hr2Tex,NULL,&hr29);
                            SDL_DestroyTexture(imageTexture);


                            SDL_Rect hr30 = {SCREEN_WIDTH / 22+20,SCREEN_HEIGHT / 22+370, SCREEN_WIDTH / 5, SCREEN_HEIGHT / 5};

                            // loadFromFile("horizontalroad2.png");
                            SDL_RenderCopy(gRenderer,hr2Tex,NULL,&hr30);
                            SDL_DestroyTexture(imageTexture);


                            SDL_Rect hr31 = {SCREEN_WIDTH / 22+150+175,SCREEN_HEIGHT / 22+440, SCREEN_WIDTH / 5, SCREEN_HEIGHT / 5};

                            // loadFromFile("horizontalroad2.png");
                            SDL_RenderCopy(gRenderer,hr2Tex,NULL,&hr31);
                            SDL_DestroyTexture(imageTexture);


                            SDL_Rect vr17 = {SCREEN_WIDTH / 22+150+95+168,SCREEN_HEIGHT / 22+410, SCREEN_WIDTH / 5, SCREEN_HEIGHT / 5};

                            // loadFromFile("verticalroad.png");
                            SDL_RenderCopy(gRenderer,vrTex,NULL,&vr17);
                            SDL_DestroyTexture(imageTexture);

                            SDL_Rect vr18 = {SCREEN_WIDTH / 22+150+95+168,SCREEN_HEIGHT / 22+450, SCREEN_WIDTH / 5, SCREEN_HEIGHT / 5};

                            // loadFromFile("verticalroad.png");
                            SDL_RenderCopy(gRenderer,vrTex,NULL,&vr18);
                            SDL_DestroyTexture(imageTexture);

                            SDL_Rect interRoadMasalaMix = {SCREEN_WIDTH / 22+95+130,SCREEN_HEIGHT / 22+425, SCREEN_WIDTH / 15, SCREEN_HEIGHT / 20};
                            SDL_RenderCopy(gRenderer,interConnectingRoadsTex,NULL,&interRoadMasalaMix);


                            SDL_Rect interRoadRajdhani = {SCREEN_WIDTH / 22+95+130+100,SCREEN_HEIGHT / 22+425, SCREEN_WIDTH / 15, SCREEN_HEIGHT / 20};
                            SDL_RenderCopy(gRenderer,interConnectingRoadsTex,NULL,&interRoadRajdhani);

                            SDL_Rect interRoadChaayos = {SCREEN_WIDTH / 22+95+130+200,SCREEN_HEIGHT / 22+425, SCREEN_WIDTH / 15, SCREEN_HEIGHT / 20};
                            SDL_RenderCopy(gRenderer,interConnectingRoadsTex,NULL,&interRoadChaayos);

                            SDL_Rect interRoadZanskar = {SCREEN_WIDTH / 22+95+130+40,SCREEN_HEIGHT / 22+280, SCREEN_WIDTH / 15, SCREEN_HEIGHT / 20};
                            SDL_RenderCopy(gRenderer,interConnectingRoadsTex,NULL,&interRoadZanskar);

                            SDL_Rect interRoadShivalik = {SCREEN_WIDTH / 22+95+130+40+100,SCREEN_HEIGHT / 22+280, SCREEN_WIDTH / 15, SCREEN_HEIGHT / 20};
                            SDL_RenderCopy(gRenderer,interConnectingRoadsTex,NULL,&interRoadShivalik);

                            SDL_Rect interRoadDeli16 = {SCREEN_WIDTH / 22+95+130+40+160,SCREEN_HEIGHT / 22+134, SCREEN_WIDTH / 15, SCREEN_HEIGHT / 20};
                            SDL_RenderCopy(gRenderer,interConnectingRoadsTex,NULL,&interRoadDeli16);

                            SDL_Rect interRoadArav = {SCREEN_WIDTH / 22+95+130+40+160,SCREEN_HEIGHT / 22+100, SCREEN_WIDTH / 15, SCREEN_HEIGHT / 20};
                            SDL_RenderCopy(gRenderer,interConnectingRoadsTex,NULL,&interRoadArav);

                            SDL_Rect interRoadKara = {SCREEN_WIDTH / 22+95+130,SCREEN_HEIGHT / 22+100, SCREEN_WIDTH / 15, SCREEN_HEIGHT / 20};
                            SDL_RenderCopy(gRenderer,interConnectingRoadsTex,NULL,&interRoadKara);

                            SDL_Rect interRoadNil = {SCREEN_WIDTH / 22+25,SCREEN_HEIGHT / 22+100, SCREEN_WIDTH / 15, SCREEN_HEIGHT / 20};
                            SDL_RenderCopy(gRenderer,interConnectingRoadsTex,NULL,&interRoadNil);

                            SDL_Rect interRoadJwala = {SCREEN_WIDTH / 22+95+130+40+160+350,SCREEN_HEIGHT / 22+100, SCREEN_WIDTH / 15, SCREEN_HEIGHT / 20};
                            SDL_RenderCopy(gRenderer,interConnectingRoadsTex,NULL,&interRoadJwala);

                            SDL_Rect interRoadKum = {SCREEN_WIDTH / 22+95+130+40+160+350,SCREEN_HEIGHT / 22+130, SCREEN_WIDTH / 15, SCREEN_HEIGHT / 20};
                            SDL_RenderCopy(gRenderer,interConnectingRoadsTex,NULL,&interRoadKum);

                            SDL_Rect interRoadVindy = {SCREEN_WIDTH / 22+610,SCREEN_HEIGHT / 22+270, SCREEN_WIDTH / 10, SCREEN_HEIGHT / 10};
                            SDL_RenderCopy(gRenderer,hr2Tex,NULL,&interRoadVindy);

                            // SDL_Rect interRoadHospital = {SCREEN_WIDTH / 22,SCREEN_HEIGHT / 22+450, SCREEN_WIDTH / 6, SCREEN_HEIGHT / 6};
                            // SDL_RenderCopy(gRenderer,hr2Tex,NULL,&interRoadHospital);

                            SDL_Rect interRoadGroundHospital = {SCREEN_WIDTH / 22-15,SCREEN_HEIGHT / 22+450, SCREEN_WIDTH / 6, SCREEN_HEIGHT / 6};
                            SDL_RenderCopy(gRenderer,hr2Tex,NULL,&interRoadGroundHospital);

                            SDL_Rect interRoadStaffCanteen = {SCREEN_WIDTH / 22+10,SCREEN_HEIGHT / 22+700, SCREEN_WIDTH / 8, SCREEN_HEIGHT / 6};
                            SDL_RenderCopy(gRenderer,hr2Tex,NULL,&interRoadStaffCanteen);


                            SDL_Rect interRoadLHC = {SCREEN_WIDTH / 22+20,SCREEN_HEIGHT / 22+780, SCREEN_WIDTH / 8, SCREEN_HEIGHT / 6};
                            SDL_RenderCopy(gRenderer,hr2Tex,NULL,&interRoadLHC);


                            SDL_Rect interRoadAmul = {SCREEN_WIDTH / 22+610,SCREEN_HEIGHT / 22+695, SCREEN_WIDTH / 18, SCREEN_HEIGHT / 18};
                            SDL_RenderCopy(gRenderer,interConnectingRoadsTex,NULL,&interRoadAmul);

                            SDL_Rect interRoadShiru = {SCREEN_WIDTH / 22+480,SCREEN_HEIGHT / 22+695, SCREEN_WIDTH / 18, SCREEN_HEIGHT / 18};
                            SDL_RenderCopy(gRenderer,interConnectingRoadsTex,NULL,&interRoadShiru);


                            SDL_Rect interRoadNescafe = {SCREEN_WIDTH / 22+760,SCREEN_HEIGHT / 22+695, SCREEN_WIDTH / 18, SCREEN_HEIGHT / 18};
                            SDL_RenderCopy(gRenderer,interConnectingRoadsTex,NULL,&interRoadNescafe);

                            SDL_Rect interRoadCcd = {SCREEN_WIDTH / 22+860,SCREEN_HEIGHT / 22+760, SCREEN_WIDTH / 15, SCREEN_HEIGHT / 8};
                            SDL_RenderCopy(gRenderer,hr2Tex,NULL,&interRoadCcd);


                            SDL_Rect interRoadTennis = {SCREEN_WIDTH / 22+260,SCREEN_HEIGHT / 22+229, SCREEN_WIDTH / 15, SCREEN_HEIGHT / 15};
                            SDL_RenderCopy(gRenderer,vrTex,NULL,&interRoadTennis);

                            SDL_Rect interRoadVolley = {SCREEN_WIDTH / 22+410,SCREEN_HEIGHT / 22+229, SCREEN_WIDTH / 15, SCREEN_HEIGHT / 15};
                            SDL_RenderCopy(gRenderer,vrTex,NULL,&interRoadVolley);

                            pair<int,int> pr= generateRandomPoint(10);
                            // delay has occured
                            


                            SDL_Rect angryProfessor1 = {pr.first,pr.second,100,100};
                            SDL_RenderCopy(gRenderer,angryProfessorTex,NULL,&angryProfessor1);

                            pair<int,int> prd= generateRandomPoint(5);
                            SDL_Rect dog = {prd.first,prd.second,60,60};
                            SDL_RenderCopy(gRenderer,hungryDogTex,NULL,&dog);

                            if(manhattanDistance({player1.x,player1.y},pr)<100 && notScolded){
                                notScolded = false;
                                player1.happiness = max(player1.happiness-10,0);
                                
                            }
                            if(manhattanDistance({player1.x,player1.y},pr)>=100){
                                notScolded = true;
                            }

                            if(manhattanDistance({player1.x,player1.y},prd)<100 && hungry){
                                hungry = false;
                                player1.money = max(player1.money-10,0);
                                
                            }
                            if(manhattanDistance({player1.x,player1.y},prd)>=100){
                                hungry = true;
                            }

                            //YULU

                            SDL_Rect yulu1 = {150,344,80,70};
                            SDL_RenderCopy(gRenderer,yuluTex,NULL,&yulu1);

                            SDL_Rect yulu2 = {173,444,80,70};
                            SDL_RenderCopy(gRenderer,yuluTex,NULL,&yulu2);


                            SDL_Rect yulu3 = {173,649,80,70};
                            SDL_RenderCopy(gRenderer,yuluTex,NULL,&yulu3);

                            SDL_Rect yulu4 = {173,829,80,70};
                            SDL_RenderCopy(gRenderer,yuluTex,NULL,&yulu4);


                            SDL_Rect yulu5 = {594,524,80,70};
                            SDL_RenderCopy(gRenderer,yuluTex,NULL,&yulu5);

                            SDL_Rect yulu6 = {915,954,80,70};
                            SDL_RenderCopy(gRenderer,yuluTex,NULL,&yulu6);

                            SDL_Rect yulu7 = {955,144,80,70};
                            SDL_RenderCopy(gRenderer,yuluTex,NULL,&yulu7);


                            SDL_Rect yuluTop = {1220,104,300,300};
                            if(player1.takenYulu){
                                SDL_RenderCopy(gRenderer,yuluTopTex,NULL,&yuluTop);
                            }
                ///////////////////////////////////////////////////////////////////


                            // SDL_Surface* textSurface = TTF_RenderText_Shaded(font, totalKilled,    foregroundColor, backgroundColor);


                            // SDL_SetRenderDrawColor( gRenderer,235, 52, 155, 0xFF );
                            player1.renderPlayer();
                            if(player2.inMain){
                                player2.renderPlayer();
                            }
                            

                            
                            


                                    while( SDL_PollEvent( &e ) != 0 )
                                        {
                                                //User requests quit
                                                if( e.type == SDL_QUIT )
                                                {
                                                        quit = true;
                                                }
                                                else if(e.type == SDL_KEYDOWN){
                                                        switch (e.key.keysym.sym){
                                                                case SDLK_UP:
                                                                        player1.move(KEY_PRESS_UP);
                                                                        player1.lastStepDirection = 1;
                                                                        break;
                                                                case SDLK_DOWN:
                                                                        player1.move(KEY_PRESS_DOWN);
                                                                        player1.lastStepDirection = 0;
                                                                        break;
                                                                case SDLK_LEFT:
                                                                        player1.lastStepDirection = 2;
                                                                        player1.move(KEY_PRESS_LEFT);
                                                                        break;
                                                                case SDLK_RIGHT:
                                                                        player1.lastStepDirection = 3;
                                                                        player1.move(KEY_PRESS_RIGHT);
                                                                        break;
                                                                case SDLK_e:
                                                                        player1.enter();
                                                                        break;
                                                                case SDLK_y:
                                                                        player1.changeYulu();
                                                                        break;
                                                        }
                                                }
                                                SDL_SetRenderDrawColor( gRenderer,235, 52, 155, 0xFF );
                                                player1.renderPlayer();

                                        }
                                }
                else if(player1.enterHostel){

                    
                        // loading background
                    SDL_Rect tile = {  0 , 0, SCREEN_WIDTH, SCREEN_HEIGHT };
                    SDL_RenderCopy(gRenderer,tileTex,NULL,&tile);                        
                    

                    // loading tt table
                    SDL_Rect ttable = {  800 , 30, 250, 250 };
                    SDL_RenderCopy(gRenderer,ttableTex,NULL,&ttable);

                    // loading messarea
                    SDL_Rect mess = {  300 , 10, 400, 400 };
                    SDL_RenderCopy(gRenderer,messTex,NULL,&mess);                    


                    // load grass
                    SDL_Rect grass = {  300 , 400, 900, 600 };
                    SDL_RenderCopy(gRenderer,grassTex,NULL,&grass); 

                    // load rabbit1
                    SDL_Rect rabbit1 = {  300 , 400, 100, 100 };
                    
                    if((tempClip/50)%3==1){
                        SDL_RenderCopy(gRenderer,rabbitTex,NULL,&rabbit1);
                    }
                    else if((tempClip/50)%3==0){
                        SDL_RenderCopy(gRenderer,rabbitfTex,NULL,&rabbit1);
                    }
                    else if((tempClip/50)%3==2){
                        SDL_RenderCopy(gRenderer,rabbitthTex,NULL,&rabbit1);
                    }

                    // load rabbit2
                    SDL_Rect rabbit2 = {  300+800 , 400+400, 100, 100 };
                    if((tempClip/50)%3==1){
                        SDL_RenderCopy(gRenderer,rabbitTex,NULL,&rabbit2);
                    }
                    else if((tempClip/50)%3==0){
                        SDL_RenderCopy(gRenderer,rabbitfTex,NULL,&rabbit2);
                    }
                    else if((tempClip/50)%3==2){
                        SDL_RenderCopy(gRenderer,rabbitthTex,NULL,&rabbit2);
                    }



                    // load rabbit3
                    SDL_Rect rabbit3 = {  500 , 500, 100, 100 };
                    if((tempClip/50)%3==1){
                        SDL_RenderCopy(gRenderer,rabbitTex,NULL,&rabbit3);
                    }
                    else if((tempClip/50)%3==0){
                        SDL_RenderCopy(gRenderer,rabbitfTex,NULL,&rabbit3);
                    }
                    else if((tempClip/50)%3==2){
                        SDL_RenderCopy(gRenderer,rabbitthTex,NULL,&rabbit3);
                    }


                    // load rabbit4
                    SDL_Rect rabbit4 = {  550 , 750, 100, 100 };
                    if((tempClip/50)%3==1){
                        SDL_RenderCopy(gRenderer,rabbitTex,NULL,&rabbit4);
                    }
                    else if((tempClip/50)%3==0){
                        SDL_RenderCopy(gRenderer,rabbitfTex,NULL,&rabbit4);
                    }
                    else if((tempClip/50)%3==2){
                        SDL_RenderCopy(gRenderer,rabbitthTex,NULL,&rabbit4);
                    }




                    // load rabbit5
                    SDL_Rect rabbit5 = {  350 , 850, 100, 100 };
                    if((tempClip/50)%3==1){
                        SDL_RenderCopy(gRenderer,rabbitTex,NULL,&rabbit5);
                    }
                    else if((tempClip/50)%3==0){
                        SDL_RenderCopy(gRenderer,rabbitfTex,NULL,&rabbit5);
                    }
                    else if((tempClip/50)%3==2){
                        SDL_RenderCopy(gRenderer,rabbitthTex,NULL,&rabbit5);
                    }



                    // load rabbit6
                    SDL_Rect rabbit6 = {  650 , 750, 100, 100 };
                    if((tempClip/50)%3==1){
                        SDL_RenderCopy(gRenderer,rabbitTex,NULL,&rabbit6);
                    }
                    else if((tempClip/50)%3==0){
                        SDL_RenderCopy(gRenderer,rabbitfTex,NULL,&rabbit6);
                    }
                    else if((tempClip/50)%3==2){
                        SDL_RenderCopy(gRenderer,rabbitthTex,NULL,&rabbit6);
                    }




                    // load rabbit7
                    SDL_Rect rabbit7 = {  850 , 650, 100, 100 };
                    if((tempClip/50)%3==1){
                        SDL_RenderCopy(gRenderer,rabbitTex,NULL,&rabbit7);
                    }
                    else if((tempClip/50)%3==0){
                        SDL_RenderCopy(gRenderer,rabbitfTex,NULL,&rabbit7);
                    }
                    else if((tempClip/50)%3==2){
                        SDL_RenderCopy(gRenderer,rabbitthTex,NULL,&rabbit7);
                    }


                    // load room
                    SDL_Rect room = {  1200 , 200, 300, 300 };

                    SDL_RenderCopy(gRenderer,roomTex,NULL,&room); 


                    // rendering trees
                    
                    SDL_Rect tree_top = {  1140 , 850, 200, 200 };

                    SDL_RenderCopy(gRenderer,tree_topTex,NULL,&tree_top);

                    tree_top = {  160 , 850, 200, 200 };

                    SDL_RenderCopy(gRenderer,tree_topTex,NULL,&tree_top);

                    tree_top = {  1140 , 280, 200, 200 };

                    SDL_RenderCopy(gRenderer,tree_rightTex,NULL,&tree_top);

                    tree_top = {  230 , 250, 200, 200 };

                    SDL_RenderCopy(gRenderer,tree_leftTex,NULL,&tree_top);

                    // entry exit

                    SDL_Rect entry_exit = {  0 , 50, 300, 300 };

                    SDL_RenderCopy(gRenderer,entry_exitTex,NULL,&entry_exit);

                    // caretaker office

                    SDL_Rect caretaker = {  0 , 600, 300, 300 };

                    SDL_RenderCopy(gRenderer,caretakerTex,NULL,&caretaker);

                    // washroom

                    SDL_Rect washroom = { 1180 , 600, 200, 200 };

                    SDL_RenderCopy(gRenderer,washroomTex,NULL,&washroom);

                    SDL_SetRenderDrawColor( gRenderer,235, 52, 155, 0xFF );
                    SDL_Rect workers = {50,800,250/3,250};
                    SDL_RenderCopy(gRenderer,workerSprites,&arr[(tempClip/20)%3],&workers);
                    SDL_Rect workers2 = {50,300,250/3,250};
                    SDL_RenderCopy(gRenderer,workerSprites,&arr[(tempClip/20)%3],&workers2);

                    if(temp2Clip <270){
                            if((temp2Clip/30)%9==0){
                                SDL_RenderCopy(gRenderer,ttframe2Tex,NULL,&ttable);
                            }
                            else if((temp2Clip/30)%9==1){
                                SDL_RenderCopy(gRenderer,ttframe3Tex,NULL,&ttable);
                            }
                            else if((temp2Clip/30)%9==2){
                                SDL_RenderCopy(gRenderer,ttframe4Tex,NULL,&ttable);
                            }
                            else if((temp2Clip/30)%9==3){
                                SDL_RenderCopy(gRenderer,ttframe5Tex,NULL,&ttable);
                            }
                            else if((temp2Clip/30)%9==4){
                                SDL_RenderCopy(gRenderer,ttframe6Tex,NULL,&ttable);
                            }
                            else if((temp2Clip/30)%9==5){
                                SDL_RenderCopy(gRenderer,ttframe7Tex,NULL,&ttable);
                            }
                            else if((temp2Clip/30)%9==6){
                                SDL_RenderCopy(gRenderer,ttframe8Tex,NULL,&ttable);
                            }
                            else if((temp2Clip/30)%9==7){
                                SDL_RenderCopy(gRenderer,ttframe9Tex,NULL,&ttable);
                            }
                            else if((temp2Clip/30)%9==8){
                                SDL_RenderCopy(gRenderer,ttframe10Tex,NULL,&ttable);
                            }
                            
                    }

                    if(temp3Clip <120){
                            if((temp3Clip/30)%4==0){
                                SDL_RenderCopy(gRenderer,messframe1Tex,NULL,&mess);
                            }
                            else if((temp3Clip/30)%4==1){
                                SDL_RenderCopy(gRenderer,messframe2Tex,NULL,&mess);
                            }
                            else if((temp3Clip/30)%4==2){
                                SDL_RenderCopy(gRenderer,messframe3Tex,NULL,&mess);
                            }
                            else if((temp3Clip/30)%4==3){
                                SDL_RenderCopy(gRenderer,messframe4Tex,NULL,&mess);
                            }
                    }

                    temp3Clip+=1;
                    temp2Clip+=1;
                    tempClip = tempClip+1;
                    player1.renderPlayer();
                    if(player2.enterHostel){
                        player2.renderPlayer();
                    }
                    while( SDL_PollEvent( &e ) != 0 )
                        {
                                //User requests quit
                                if( e.type == SDL_QUIT )
                                {
                                        quit = true;
                                }
                                else if(e.type == SDL_KEYDOWN){
                                        switch (e.key.keysym.sym){
                                                                case SDLK_UP:
                                                                        player1.move(KEY_PRESS_UP);
                                                                        player1.lastStepDirection = 1;
                                                                        break;
                                                                case SDLK_DOWN:
                                                                        player1.move(KEY_PRESS_DOWN);
                                                                        player1.lastStepDirection = 0;
                                                                        break;
                                                                case SDLK_LEFT:
                                                                        player1.move(KEY_PRESS_LEFT);
                                                                        player1.lastStepDirection = 2;
                                                                        break;
                                                                case SDLK_RIGHT:
                                                                        player1.move(KEY_PRESS_RIGHT);
                                                                        player1.lastStepDirection = 3;
                                                                        break;
                                                                case SDLK_e:
                                                                        player1.enter();


                                        }
                                }
                                
                        }
                }

                else if(player1.inLargeGround){
                        SDL_Rect largeGroundInner= {0,0,SCREEN_WIDTH,SCREEN_HEIGHT};
                        SDL_RenderCopy(gRenderer,largeGroundInnerTex,NULL,&largeGroundInner);
                        SDL_Rect exit1= {1300,400,300,300};
                        SDL_RenderCopy(gRenderer,exitTex,NULL,&exit1);

                        SDL_SetRenderDrawColor( gRenderer,235, 52, 155, 0xFF );
                        player1.renderPlayer();
                        if(player2.inLargeGround){
                                player2.renderPlayer();
                        }
                        while( SDL_PollEvent( &e ) != 0 )
                        {
                                //User requests quit
                                if( e.type == SDL_QUIT )
                                {
                                        quit = true;
                                }
                                else if(e.type == SDL_KEYDOWN){
                                        switch (e.key.keysym.sym){
                                                                 case SDLK_UP:
                                                                        player1.move(KEY_PRESS_UP);
                                                                        player1.lastStepDirection = 1;
                                                                        break;
                                                                case SDLK_DOWN:
                                                                        player1.move(KEY_PRESS_DOWN);
                                                                        player1.lastStepDirection = 0;
                                                                        break;
                                                                case SDLK_LEFT:
                                                                        player1.move(KEY_PRESS_LEFT);
                                                                        player1.lastStepDirection = 2;
                                                                        break;
                                                                case SDLK_RIGHT:
                                                                        player1.move(KEY_PRESS_RIGHT);
                                                                        player1.lastStepDirection = 3;
                                                                        break;
                                                                case SDLK_e:
                                                                        player1.enter();
                                        }
                                }
                                
                        }

                        if(temp6Clip <180){
                            if((temp6Clip/30)%6==0){
                                SDL_RenderCopy(gRenderer,footballframe1Tex,NULL,&largeGroundInner);
                            }
                            else if((temp6Clip/30)%6==1){
                                SDL_RenderCopy(gRenderer,footballframe2Tex,NULL,&largeGroundInner);
                            }
                            else if((temp6Clip/30)%6==2){
                                SDL_RenderCopy(gRenderer,footballframe3Tex,NULL,&largeGroundInner);
                            }
                            else if((temp6Clip/30)%6==3){
                                SDL_RenderCopy(gRenderer,footballframe4Tex,NULL,&largeGroundInner);
                            }
                            else if((temp6Clip/30)%6==4){
                                SDL_RenderCopy(gRenderer,footballframe5Tex,NULL,&largeGroundInner);
                            }
                            else if((temp6Clip/30)%6==5){
                                SDL_RenderCopy(gRenderer,footballframe6Tex,NULL,&largeGroundInner);
                            }
                        }
                        temp6Clip+=1;

                        if(temp7Clip <180){
                            if((temp7Clip/30)%6==0){
                                SDL_RenderCopy(gRenderer,cricketframe1Tex,NULL,&largeGroundInner);
                            }
                            else if((temp7Clip/30)%6==1){
                                SDL_RenderCopy(gRenderer,cricketframe2Tex,NULL,&largeGroundInner);
                            }
                            else if((temp7Clip/30)%6==2){
                                SDL_RenderCopy(gRenderer,cricketframe3Tex,NULL,&largeGroundInner);
                            }
                            else if((temp7Clip/30)%6==3){
                                SDL_RenderCopy(gRenderer,cricketframe4Tex,NULL,&largeGroundInner);
                            }
                            else if((temp7Clip/30)%6==4){
                                SDL_RenderCopy(gRenderer,cricketframe5Tex,NULL,&largeGroundInner);
                            }
                            else if((temp7Clip/30)%6==5){
                                SDL_RenderCopy(gRenderer,cricketframe6Tex,NULL,&largeGroundInner);
                            }
                        }
                        temp7Clip+=1;


                        if(temp8Clip <270){
                            if((temp8Clip/30)%9==0){
                                SDL_RenderCopy(gRenderer,hockeyframe1Tex,NULL,&largeGroundInner);
                            }
                            else if((temp8Clip/30)%9==1){
                                SDL_RenderCopy(gRenderer,hockeyframe2Tex,NULL,&largeGroundInner);
                            }
                            else if((temp8Clip/30)%9==2){
                                SDL_RenderCopy(gRenderer,hockeyframe3Tex,NULL,&largeGroundInner);
                            }
                            else if((temp8Clip/30)%9==3){
                                SDL_RenderCopy(gRenderer,hockeyframe4Tex,NULL,&largeGroundInner);
                            }
                            else if((temp8Clip/30)%9==4){
                                SDL_RenderCopy(gRenderer,hockeyframe5Tex,NULL,&largeGroundInner);
                            }
                            else if((temp8Clip/30)%9==5){
                                SDL_RenderCopy(gRenderer,hockeyframe6Tex,NULL,&largeGroundInner);
                            }
                            else if((temp8Clip/30)%9==6){
                                SDL_RenderCopy(gRenderer,hockeyframe7Tex,NULL,&largeGroundInner);
                            }
                            else if((temp8Clip/30)%9==7){
                                SDL_RenderCopy(gRenderer,hockeyframe8Tex,NULL,&largeGroundInner);
                            }
                            else if((temp8Clip/30)%9==8){
                                SDL_RenderCopy(gRenderer,hockeyframe9Tex,NULL,&largeGroundInner);
                            }
                        }
                        temp8Clip+=1;
                        
                }

                else if(player1.inTennisCourt){
                        SDL_Rect tennisCourtInner= {0,0,SCREEN_WIDTH,SCREEN_HEIGHT};
                        SDL_RenderCopy(gRenderer,tennisCourtInnerTex,NULL,&tennisCourtInner);
                        SDL_Rect exit1= {1300,400,300,300};
                        SDL_RenderCopy(gRenderer,exitTex,NULL,&exit1);

                        SDL_SetRenderDrawColor( gRenderer,235, 52, 155, 0xFF );
                        player1.renderPlayer();
                        if(player2.inTennisCourt){
                                player2.renderPlayer();
                        }
                        while( SDL_PollEvent( &e ) != 0 )
                        {
                                //User requests quit
                                if( e.type == SDL_QUIT )
                                {
                                        quit = true;
                                }
                                else if(e.type == SDL_KEYDOWN){
                                        switch (e.key.keysym.sym){
                                                                case SDLK_UP:
                                                                        player1.move(KEY_PRESS_UP);
                                                                        player1.lastStepDirection = 1;
                                                                        break;
                                                                case SDLK_DOWN:
                                                                player1.lastStepDirection = 0;
                                                                        player1.move(KEY_PRESS_DOWN);
                                                                        break;
                                                                case SDLK_LEFT:
                                                                player1.lastStepDirection = 2;
                                                                        player1.move(KEY_PRESS_LEFT);
                                                                        break;
                                                                case SDLK_RIGHT:
                                                                player1.lastStepDirection = 3;
                                                                        player1.move(KEY_PRESS_RIGHT);
                                                                        break;
                                                                case SDLK_e:
                                                                        player1.enter();
                                        }
                                }
                                
                        }

                        if(temp4Clip <180){
                            if((temp4Clip/30)%6==0){
                                SDL_RenderCopy(gRenderer,tennisframe1Tex,NULL,&tennisCourtInner);
                            }
                            else if((temp4Clip/30)%6==1){
                                SDL_RenderCopy(gRenderer,tennisframe2Tex,NULL,&tennisCourtInner);
                            }
                            else if((temp4Clip/30)%6==2){
                                SDL_RenderCopy(gRenderer,tennisframe3Tex,NULL,&tennisCourtInner);
                            }
                            else if((temp4Clip/30)%6==3){
                                SDL_RenderCopy(gRenderer,tennisframe4Tex,NULL,&tennisCourtInner);
                            }
                            else if((temp4Clip/30)%6==4){
                                SDL_RenderCopy(gRenderer,tennisframe5Tex,NULL,&tennisCourtInner);
                            }
                            else if((temp4Clip/30)%6==5){
                                SDL_RenderCopy(gRenderer,tennisframe6Tex,NULL,&tennisCourtInner);
                            }
                        }
                        temp4Clip+=1;
                }
                else if(player1.inVolleyCourt){
                         SDL_Rect volleyCourtInner= {0,0,SCREEN_HEIGHT,SCREEN_HEIGHT};
                        SDL_RenderCopy(gRenderer,volleyCourtInnerTex,NULL,&volleyCourtInner);
                        SDL_Rect exit1= {1300,400,300,300};
                        SDL_RenderCopy(gRenderer,exitTex,NULL,&exit1);

                        SDL_SetRenderDrawColor( gRenderer,235, 52, 155, 0xFF );
                        player1.renderPlayer();
                        if(player2.inVolleyCourt){
                                player2.renderPlayer();
                        }
                        while( SDL_PollEvent( &e ) != 0 )
                        {
                                //User requests quit
                                if( e.type == SDL_QUIT )
                                {
                                        quit = true;
                                }
                                else if(e.type == SDL_KEYDOWN){
                                        switch (e.key.keysym.sym){
                                                                case SDLK_UP:
                                                                        player1.move(KEY_PRESS_UP);
                                                                        player1.lastStepDirection = 1;
                                                                        break;
                                                                case SDLK_DOWN:
                                                                player1.lastStepDirection = 0;
                                                                        player1.move(KEY_PRESS_DOWN);
                                                                        break;
                                                                case SDLK_LEFT:
                                                                        player1.lastStepDirection = 2;
                                                                        player1.move(KEY_PRESS_LEFT);
                                                                        break;
                                                                case SDLK_RIGHT:
                                                                        player1.lastStepDirection = 3;
                                                                        player1.move(KEY_PRESS_RIGHT);
                                                                        break;
                                                                case SDLK_e:
                                                                        player1.enter();
                                        }
                                }
                                
                        }
                        if(temp5Clip<180){
                                if((temp5Clip/30)%6==0){
                                    SDL_RenderCopy(gRenderer,volleyballframeTex1,NULL,&volleyCourtInner);
                                }
                                else if((temp5Clip/30)%6==1){
                                    SDL_RenderCopy(gRenderer,volleyballframeTex2,NULL,&volleyCourtInner);
                                }
                                else if((temp5Clip/30)%6==2){
                                    SDL_RenderCopy(gRenderer,volleyballframeTex3,NULL,&volleyCourtInner);
                                }
                                else if((temp5Clip/30)%6==3){
                                    SDL_RenderCopy(gRenderer,volleyballframeTex4,NULL,&volleyCourtInner);
                                }
                                else if((temp5Clip/30)%6==4){
                                    SDL_RenderCopy(gRenderer,volleyballframeTex5,NULL,&volleyCourtInner);
                                }
                                else if((temp5Clip/30)%6==5){
                                    SDL_RenderCopy(gRenderer,volleyballframeTex6,NULL,&volleyCourtInner);
                                }
                        }
                        temp5Clip+=1;
                }
                else if(player1.inLHC){
                        SDL_Rect lhcInner = {0,0,SCREEN_HEIGHT,SCREEN_HEIGHT};
                        SDL_RenderCopy(gRenderer,LHCInnerTex,NULL,&lhcInner);
                        SDL_Rect exit1= {1300,400,300,300};
                        SDL_RenderCopy(gRenderer,exitTex,NULL,&exit1);

                        SDL_SetRenderDrawColor( gRenderer,235, 52, 155, 0xFF );
                        player1.renderPlayer();
                        if(player2.inLHC){
                                player2.renderPlayer();
                        }
                        while( SDL_PollEvent( &e ) != 0 )
                        {
                                //User requests quit
                                if( e.type == SDL_QUIT )
                                {
                                        quit = true;
                                }
                                else if(e.type == SDL_KEYDOWN){
                                        switch (e.key.keysym.sym){
                                                                case SDLK_UP:
                                                                        player1.lastStepDirection = 1;
                                                                        player1.move(KEY_PRESS_UP);
                                                                        break;
                                                                case SDLK_DOWN:
                                                                        player1.lastStepDirection = 0;
                                                                        player1.move(KEY_PRESS_DOWN);
                                                                        break;
                                                                case SDLK_LEFT:
                                                                        player1.lastStepDirection = 2;
                                                                        player1.move(KEY_PRESS_LEFT);
                                                                        break;
                                                                case SDLK_RIGHT:
                                                                        player1.lastStepDirection = 3;
                                                                        player1.move(KEY_PRESS_RIGHT);
                                                                        break;
                                                                case SDLK_e:
                                                                        player1.enter();
                                        }
                                }
                                
                        }
                }
                else if(player1.inLHC108){
                        if(player1.inLHC108 || player1.inLHC114 || player1.inLHC325){
                                if(delay()){
                                        player1.knowledge=min(player1.knowledge+1,100);
                                        player1.energy = max(player1.energy-1,0);
                                        player1.health = max(player1.health-1,0);
                                        if(player1.energy==0 || player1.health ==0){
                                                player1.hospitalize();
                                        }

                                }
                        }
                        SDL_Rect lhc108 = {0,0,SCREEN_HEIGHT,SCREEN_HEIGHT};
                        SDL_RenderCopy(gRenderer,LH108Tex,NULL,&lhc108);
                        SDL_Rect exit1= {1300,400,300,300};
                        SDL_RenderCopy(gRenderer,exitTex,NULL,&exit1);

                        SDL_SetRenderDrawColor( gRenderer,235, 52, 155, 0xFF );
                        player1.renderPlayer();
                        if(player2.inLHC108){
                                player2.renderPlayer();
                        }
                        while( SDL_PollEvent( &e ) != 0 )
                        {
                                //User requests quit
                                if( e.type == SDL_QUIT )
                                {
                                        quit = true;
                                }
                                else if(e.type == SDL_KEYDOWN){
                                        switch (e.key.keysym.sym){
                                                                case SDLK_UP:
                                                                        player1.move(KEY_PRESS_UP);
                                                                        player1.lastStepDirection = 1;
                                                                        break;
                                                                case SDLK_DOWN:
                                                                        player1.lastStepDirection = 0;
                                                                        player1.move(KEY_PRESS_DOWN);
                                                                        break;
                                                                case SDLK_LEFT:
                                                                        player1.lastStepDirection = 2;
                                                                        player1.move(KEY_PRESS_LEFT);
                                                                        break;
                                                                case SDLK_RIGHT:
                                                                        player1.lastStepDirection = 3;
                                                                        player1.move(KEY_PRESS_RIGHT);
                                                                        break;
                                                                case SDLK_e:
                                                                        player1.enter();
                                        }
                                }
                                
                        }
                }
                else if(player1.inLHC114){
                        if(player1.inLHC108 || player1.inLHC114 || player1.inLHC325){
                                if(delay()){
                                        player1.knowledge=min(player1.knowledge+1,100);
                                        player1.energy = max(player1.energy-1,0);
                                        player1.health = max(player1.health-1,0);
                                        if(player1.energy==0 || player1.health ==0){
                                                player1.hospitalize();
                                        }
                                }
                        }
                        SDL_Rect lhc114 = {0,0,SCREEN_HEIGHT,SCREEN_HEIGHT};
                        SDL_RenderCopy(gRenderer,LHC114Tex,NULL,&lhc114);
                        SDL_Rect exit1= {1300,400,300,300};
                        SDL_RenderCopy(gRenderer,exitTex,NULL,&exit1);

                        SDL_SetRenderDrawColor( gRenderer,235, 52, 155, 0xFF );
                        player1.renderPlayer();
                        if(player2.inLHC114){
                                player2.renderPlayer();
                        }
                        while( SDL_PollEvent( &e ) != 0 )
                        {
                                //User requests quit
                                if( e.type == SDL_QUIT )
                                {
                                        quit = true;
                                }
                                else if(e.type == SDL_KEYDOWN){
                                        switch (e.key.keysym.sym){
                                                                case SDLK_UP:
                                                                        player1.lastStepDirection = 1;
                                                                        player1.move(KEY_PRESS_UP);
                                                                        break;
                                                                case SDLK_DOWN:
                                                                        player1.lastStepDirection = 0;
                                                                        player1.move(KEY_PRESS_DOWN);
                                                                        break;
                                                                case SDLK_LEFT:
                                                                        player1.lastStepDirection = 2;
                                                                        player1.move(KEY_PRESS_LEFT);
                                                                        break;
                                                                case SDLK_RIGHT:
                                                                        player1.lastStepDirection = 3;
                                                                        player1.move(KEY_PRESS_RIGHT);
                                                                        break;
                                                                case SDLK_e:
                                                                        player1.enter();
                                        }
                                }
                                
                        }
                }
                else if(player1.inLHC325){
                        if(player1.inLHC108 || player1.inLHC114 || player1.inLHC325){
                                if(delay()){
                                        player1.knowledge=min(player1.knowledge+1,100);
                                        player1.energy = max(player1.energy-1,0);
                                        player1.health = max(player1.health-1,0);
                                        if(player1.energy==0 || player1.health ==0){
                                                player1.hospitalize();
                                        }
                                }
                        }
                        SDL_Rect lhc325 = {0,0,SCREEN_HEIGHT,SCREEN_HEIGHT};
                        SDL_RenderCopy(gRenderer,LHC325Tex,NULL,&lhc325);
                        SDL_Rect exit1= {1300,400,300,300};
                        SDL_RenderCopy(gRenderer,exitTex,NULL,&exit1);

                        SDL_SetRenderDrawColor( gRenderer,235, 52, 155, 0xFF );
                        player1.renderPlayer();
                        if(player2.inLHC325){
                                player2.renderPlayer();
                        }
                        while( SDL_PollEvent( &e ) != 0 )
                        {
                                //User requests quit
                                if( e.type == SDL_QUIT )
                                {
                                        quit = true;
                                }
                                else if(e.type == SDL_KEYDOWN){
                                        switch (e.key.keysym.sym){
                                                                case SDLK_UP:
                                                                        player1.lastStepDirection = 1;
                                                                        player1.move(KEY_PRESS_UP);
                                                                        break;
                                                                case SDLK_DOWN:
                                                                        player1.lastStepDirection = 0;
                                                                        player1.move(KEY_PRESS_DOWN);
                                                                        break;
                                                                case SDLK_LEFT:
                                                                        player1.lastStepDirection = 2;
                                                                        player1.move(KEY_PRESS_LEFT);
                                                                        break;
                                                                case SDLK_RIGHT:
                                                                        player1.lastStepDirection = 3;
                                                                        player1.move(KEY_PRESS_RIGHT);
                                                                        break;
                                                                case SDLK_e:
                                                                        player1.enter();
                                        }
                                }
                                
                        }
                }
                else if(player1.enterRestaurant){

                        // loading background
                    
                        // cout<<insufficientMoney<<"\n";
                    if(delay() && insufficientMoney){
                        insufficientMoney = false;
                    }
                    SDL_Rect tile = {  0 , 0, SCREEN_WIDTH, SCREEN_HEIGHT };
                    SDL_RenderCopy(gRenderer,restaurantTex,NULL,&tile);
                    

                    SDL_SetRenderDrawColor( gRenderer,235, 52, 155, 0xFF );
                    player1.renderPlayer();
                    if(player2.enterRestaurant){
                        player2.renderPlayer();
                    }
                    while( SDL_PollEvent( &e ) != 0 )
                        {
                                //User requests quit
                                if( e.type == SDL_QUIT )
                                {
                                        quit = true;
                                }
                                else if(e.type == SDL_KEYDOWN){
                                        switch (e.key.keysym.sym){
                                                                case SDLK_UP:
                                                                        player1.lastStepDirection = 1;
                                                                        player1.move(KEY_PRESS_UP);
                                                                        break;
                                                                case SDLK_DOWN:
                                                                        player1.lastStepDirection = 0;
                                                                        player1.move(KEY_PRESS_DOWN);
                                                                        break;
                                                                case SDLK_LEFT:
                                                                        player1.lastStepDirection = 2;
                                                                        player1.move(KEY_PRESS_LEFT);
                                                                        break;
                                                                case SDLK_RIGHT:
                                                                        player1.lastStepDirection = 3;
                                                                        player1.move(KEY_PRESS_RIGHT);
                                                                        break;
                                                                case SDLK_e:
                                                                        player1.enter();
                                        }
                                }
                                
                        }
                        if(insufficientMoney){

                                SDL_Rect insufficient = {100,30,400,400};
                                SDL_RenderCopy(gRenderer,insufficientMoneyTex,NULL,&insufficient);
                        }
                }
                else if(player1.enterSAC){

                        // loading background
                    SDL_Rect tile = {  0 , 0, SCREEN_WIDTH, SCREEN_HEIGHT };
                    SDL_RenderCopy(gRenderer,SACinsideTex,NULL,&tile);

                    SDL_SetRenderDrawColor( gRenderer,235, 52, 155, 0xFF );
                    player1.renderPlayer();
                    if(player2.enterSAC){
                        player2.renderPlayer();
                    }
                        while( SDL_PollEvent( &e ) != 0 )
                        {
                                //User requests quit
                                if( e.type == SDL_QUIT )
                                {
                                        quit = true;
                                }
                                else if(e.type == SDL_KEYDOWN){
                                        switch (e.key.keysym.sym){
                                                                case SDLK_UP:
                                                                        player1.lastStepDirection = 1;
                                                                        player1.move(KEY_PRESS_UP);
                                                                        break;
                                                                case SDLK_DOWN:
                                                                        player1.lastStepDirection = 0;
                                                                        player1.move(KEY_PRESS_DOWN);
                                                                        break;
                                                                case SDLK_LEFT:
                                                                        player1.lastStepDirection = 2;
                                                                        player1.move(KEY_PRESS_LEFT);
                                                                        break;
                                                                case SDLK_RIGHT:
                                                                        player1.lastStepDirection = 3;
                                                                        player1.move(KEY_PRESS_RIGHT);
                                                                        break;
                                                                case SDLK_e:
                                                                        player1.enter();
                                        }
                                }
                                
                        }

                        if(temp9Clip<100){
                                if((temp9Clip/20)%5==0){
                                    SDL_RenderCopy(gRenderer,badmintonframeTex1,NULL,&tile);
                                }
                                else if((temp9Clip/20)%5==1){
                                    SDL_RenderCopy(gRenderer,gymframeTex1,NULL,&tile);
                                }
                                else if((temp9Clip/20)%5==2){
                                    SDL_RenderCopy(gRenderer,gymframeTex2,NULL,&tile);
                                }
                                else if((temp9Clip/20)%5==3){
                                    SDL_RenderCopy(gRenderer,gymframeTex1,NULL,&tile);
                                }
                                else if((temp9Clip/20)%5==4){
                                    SDL_RenderCopy(gRenderer,badmintonframeTex1,NULL,&tile);
                                }
                                
                        }
                        temp9Clip+=1;


                        if(temp10Clip<100){
                                if((temp10Clip/20)%5==0){
                                    SDL_RenderCopy(gRenderer,badmintonframeTex1,NULL,&tile);
                                }
                                else if((temp10Clip/20)%5==1){
                                    SDL_RenderCopy(gRenderer,badmintonframeTex2,NULL,&tile);
                                }
                                else if((temp10Clip/20)%5==2){
                                    SDL_RenderCopy(gRenderer,badmintonframeTex3,NULL,&tile);
                                }
                                else if((temp10Clip/20)%5==3){
                                    SDL_RenderCopy(gRenderer,badmintonframeTex4,NULL,&tile);
                                }
                                else if((temp10Clip/20)%5==4){
                                    SDL_RenderCopy(gRenderer,badmintonframeTex5,NULL,&tile);
                                }
                                
                        }
                        temp10Clip+=1;
                }
                else if(player1.enterLibrary){

                        // loading background
                    SDL_Rect tile = {  0 , 0, SCREEN_WIDTH, SCREEN_HEIGHT };
                    SDL_RenderCopy(gRenderer,libraryinsideTex,NULL,&tile);
                    SDL_Rect exit1= {1300,400,300,300};
                    SDL_RenderCopy(gRenderer,exitTex,NULL,&exit1);
                    SDL_SetRenderDrawColor( gRenderer,235, 52, 155, 0xFF );
                    player1.renderPlayer();
                    if(player2.enterLibrary){
                        player2.renderPlayer();
                    }
                        while( SDL_PollEvent( &e ) != 0 )
                        {
                                //User requests quit
                                if( e.type == SDL_QUIT )
                                {
                                        quit = true;
                                }
                                else if(e.type == SDL_KEYDOWN){
                                        switch (e.key.keysym.sym){
                                                                case SDLK_UP:
                                                                        player1.lastStepDirection = 1;
                                                                        player1.move(KEY_PRESS_UP);
                                                                        break;
                                                                case SDLK_DOWN:
                                                                        player1.lastStepDirection = 0;
                                                                        player1.move(KEY_PRESS_DOWN);
                                                                        break;
                                                                case SDLK_LEFT:
                                                                        player1.lastStepDirection = 2;
                                                                        player1.move(KEY_PRESS_LEFT);
                                                                        break;
                                                                case SDLK_RIGHT:
                                                                        player1.lastStepDirection = 3;
                                                                        player1.move(KEY_PRESS_RIGHT);
                                                                        break;
                                                                case SDLK_e:
                                                                        player1.enter();
                                        }
                                }
                                
                        }
                }
                else if(player1.isSleeping){
                    SDL_Rect sleep = {0,0,SCREEN_HEIGHT,SCREEN_HEIGHT};
                    SDL_RenderCopy(gRenderer,sleepTex,NULL,&sleep);
                    if(delay()){
                                        player1.energy = min(player1.energy+1,100);
                                        player1.health = min(player1.health+1,100);
                    }
                    SDL_SetRenderDrawColor( gRenderer,235, 52, 155, 0xFF );
                    while( SDL_PollEvent( &e ) != 0 )
                        {
                                //User requests quit
                                if( e.type == SDL_QUIT )
                                {
                                        quit = true;
                                }
                                else if(e.type == SDL_KEYDOWN){
                                        switch (e.key.keysym.sym){
                                                                case SDLK_UP:
                                                                        player1.lastStepDirection = 1;
                                                                        player1.move(KEY_PRESS_UP);
                                                                        break;
                                                                case SDLK_DOWN:
                                                                        player1.lastStepDirection = 0;
                                                                        player1.move(KEY_PRESS_DOWN);
                                                                        break;
                                                                case SDLK_LEFT:
                                                                        player1.lastStepDirection = 2;
                                                                        player1.move(KEY_PRESS_LEFT);
                                                                        break;
                                                                case SDLK_RIGHT:
                                                                        player1.lastStepDirection = 3;
                                                                        player1.move(KEY_PRESS_RIGHT);
                                                                        break;
                                                                case SDLK_w:
                                                                        player1.enter();
                                        }
                                }
                                
                        }

                }

                else if(player1.isStudying){
                    SDL_Rect study = {0,0,SCREEN_HEIGHT,SCREEN_HEIGHT};
                    SDL_RenderCopy(gRenderer,studyTex,NULL,&study);
                    if(delay()){

                                        player1.energy = max(player1.energy-1,0);
                                        player1.health = max(player1.health-1,0);
                                        player1.knowledge = min(player1.knowledge+1,100);
                                        if(player1.health<=0 || player1.energy<=0){
                                                player1.hospitalize();
                                        }
                    }
                    SDL_SetRenderDrawColor( gRenderer,235, 52, 155, 0xFF );
                    while( SDL_PollEvent( &e ) != 0 )
                        {
                                //User requests quit
                                if( e.type == SDL_QUIT )
                                {
                                        quit = true;
                                }
                                else if(e.type == SDL_KEYDOWN){
                                        switch (e.key.keysym.sym){
                                                                case SDLK_UP:
                                                                        player1.lastStepDirection = 1;
                                                                        player1.move(KEY_PRESS_UP);
                                                                        break;
                                                                case SDLK_DOWN:
                                                                        player1.lastStepDirection = 0;
                                                                        player1.move(KEY_PRESS_DOWN);
                                                                        break;
                                                                case SDLK_LEFT:
                                                                        player1.lastStepDirection = 2;
                                                                        player1.move(KEY_PRESS_LEFT);
                                                                        break;
                                                                case SDLK_RIGHT:
                                                                        player1.lastStepDirection = 3;
                                                                        player1.move(KEY_PRESS_RIGHT);
                                                                        break;
                                                                case SDLK_w:
                                                                        player1.enter();
                                        }
                                }
                                
                        }

                }
                
                    

        string s= "Player happiness:-"+to_string(player1.happiness);
        int n = s.length();
        char char_array1[n + 1];
        strcpy(char_array1, s.c_str());
        disptext(gRenderer,  SCREEN_WIDTH-160,750,140,50, char_array1,235, 52, 155) ;

        s= "Player money:-"+to_string(player1.money);
        n = s.length();
        char char_array2[n + 1];
        strcpy(char_array2, s.c_str());
        disptext(gRenderer,  SCREEN_WIDTH-160,700,140,50, char_array2,235, 52, 155) ;

        s= "Player knowledge:-"+to_string(player1.knowledge);
        n = s.length();
        char char_array3[n + 1];
        strcpy(char_array3, s.c_str());
        disptext(gRenderer,  SCREEN_WIDTH-160,650,140,50, char_array3,235, 52, 155) ;

        s= "Player energy:-"+to_string(player1.energy);
        n = s.length();
        char char_array4[n + 1];
        strcpy(char_array4, s.c_str());
        disptext(gRenderer,  SCREEN_WIDTH-160,600,140,50, char_array4,235, 52, 155) ;

        s= "Player health:-"+to_string(player1.health);
        n = s.length();
        char char_array5[n + 1];
        strcpy(char_array5, s.c_str());
        disptext(gRenderer,  SCREEN_WIDTH-160,800,140,50, char_array5,235, 52, 155) ;














                SDL_RenderPresent(gRenderer);                     

                }
        }








        

        



        return 0;
                
}