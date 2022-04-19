#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <SDL2_ttf/SDL_ttf.h>
#include <SDL2_mixer/SDL_mixer.h>
#include <SDL2_net/SDL_net.h>




//#include "CNet.h"


//    SDL_Color White = {static_cast<Uint8>(r), static_cast<Uint8>(g), static_cast<Uint8>(b)};

//  path="/Users/eshan/Main/OneDrive - IIT Delhi 2/Eshan/Sem-4/COP290/Task-2/sdl2-starter/src/"+path ;

//TTF_Font* Sans = TTF_OpenFont("/Library/Fonts/Arial Unicode.ttf", 30);          //CHANGE THE FONT PATH TO AN APPROPRIATE ONE ACCORDING TO YOUR SYSTEM



#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <fcntl.h>
#include <arpa/inet.h>
#define MAX 40
#define PORT 8080
#define SA struct sockaddr

#include <stdio.h>
#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <time.h>
#include "helper.h"
#include "resources.h"

int beforeJetx=0;
int beforeJety=0;
int temp2 = 0;
int temp4 = 0;
using namespace std;
const int HOSPITAL_BILL = 50;
const int SCREEN_WIDTH = 1520;
const int SCREEN_HEIGHT = 1020;
const int PLAYER_RADIUS = 10;
vector<pair<int,int>> startLocations = {{65,175},{245,310},{980,745},{665,475},{SCREEN_WIDTH-600,175}};

int temp = 0;
int lastx=0;
int lasty=0;
int mousex = 0;
int mousey = 0;

int k=0;

int tempClip = 0;
int newC = 0;
Uint32 start = 0;
bool running = false;
bool notScolded = true;
bool hungry = true;
bool insufficientMoney = false;
bool hospitalized = false;
int temp2Clip = 450;
int temp3Clip = 500;
int temp4Clip = 500;
int temp5Clip = 500;
int temp6Clip = 500;
int temp7Clip = 500;
int temp8Clip = 500;
int temp9Clip = 500;
int temp10Clip = 500;
int temp11Clip = 0;
int temp12Clip = 500;

int flose=0  ;
int fwon=0  ;


Mix_Music *musenter, *musclick, *musmusic, *muswon, *muslose, *mussport, *musyulu, *musinsufficientmoney, *museating, *muspeacock, *musdisco, *mussnoring, *musjetpack  ;      //Background Music
SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;
SDL_Texture* imageTexture = NULL;
SDL_Texture* gTexture = NULL;





//Current displayed texture


   









TTF_Font* font;







class Player{

        public:
                SDL_Texture* colorTexFront = NULL;
                SDL_Texture* colorTexBack = NULL;
                SDL_Texture* colorTexLeft = NULL;
                SDL_Texture* colorTexRight = NULL;
                SDL_Texture* cycleTexFront = NULL;
                SDL_Texture* cycleTexBack = NULL;
                SDL_Texture* cycleTexLeft = NULL;
                SDL_Texture* cycleTexRight = NULL;
                SDL_Texture* jetPackTexBack = NULL;
                SDL_Texture* jetPackTexLeft = NULL;
                SDL_Texture* jetPackTexRight = NULL;
                SDL_Texture* jetPackTexFront = NULL;
                SDL_Texture* colorTexLeft2 = NULL;
                int x;
                int y;
                int speed = 15;
                int health;
                int energy;
                int happiness;
                int money;
                int knowledge;
                bool isReady = false;
                bool inMain = false;
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
                bool won = false;
                bool lost = false;
                bool inOAT = false;
                int lastStepDirection = 0;
                bool purchasedJetPack = false;
                bool inCSC = false;

        Player(int xP,int yP,string colorP){
                health = 50;
                energy = 100;
                happiness = 50;
                money = 50;
                knowledge = 10;
                x = xP;
                y = yP;
                colorTexRight = loadFromFile(colorP+"-char-right.png");
                colorTexFront = loadFromFile(colorP+"-char-front.png");
                colorTexBack = loadFromFile(colorP+"-char-back.png");
                colorTexLeft = loadFromFile(colorP+"-char-left.png");
                cycleTexFront = loadFromFile(colorP+"-cyclefront.png");
                cycleTexBack = loadFromFile(colorP+"-cycleback.png");
                cycleTexLeft = loadFromFile(colorP+"-cycleleft.png");
                cycleTexRight = loadFromFile(colorP+"-cycleright.png");

                jetPackTexFront = loadFromFile(colorP+"-jetpackfront.png");
                jetPackTexBack = loadFromFile(colorP+"-jetpackback.png");
                jetPackTexLeft = loadFromFile(colorP+"-jetpackleft.png");
                jetPackTexRight = loadFromFile(colorP+"-jetpackright.png");


                colorTexLeft2 = loadFromFile(colorP+"-char-left.png");
        }



        void hospitalize(){
                if(money<HOSPITAL_BILL){
                    lost = true;
                    return;
                    // player loses
                }
                hospitalized = true;
                money-=HOSPITAL_BILL;
                energy = 100;
                health = 50;
                happiness = max(happiness-10, 0);
                x = 260;
                y = 550;
                inMain = true;
                enterHostel = false;
                inTennisCourt = false;
                inLargeGround = false;

        }

        

        void move(int keyPress){

                

                        if(inMain){
                                if(keyPress == KEY_PRESS_UP){
                                        if(x>=870 && x<=890 && y-speed>=140 && y<=215){
                                                y-=speed;
                                        }
                                        if(x>=520 && x<=540 && y-speed>=140 && y<=215){
                                                y-=speed;
                                        }
                                        if(x>=330 && x<=350 && y-speed>=140 && y<=215){
                                                y-=speed;
                                        }
                                        if(x>=120 && x<=145 && y-speed>=140 && y<=215){
                                                y-=speed;
                                        }
                                        if(y+speed<=190 && y-speed>=160 && x<=1000 && x>=0){
                                                y-=speed;
                                        }
                                        if(x<=255 && x>=230 && y-speed>=165){
                                                y-=speed;
                                        }
                                        if(x<=995 && x>=970 && y-speed>=730){
                                                y-=speed;
                                        }
                                        if(x<=680 && x>=650 && y-speed>=295){
                                                y-=speed;
                                        }
                                        if(x<=600 && x>=575 && y-speed>=547 && y<720){
                                                y-=speed;
                                        }

                                        if(x<=800 && x>=760 && y-speed>=172 && y<600){
                                                y-=speed;
                                        }
                                        if(x>=355 && x<=380 && y-speed>=295 && y<=600){
                                                y-=speed;
                                        }

                                        if(x>=455 && x<=480 && y-speed>=295 && y<=600){
                                                y-=speed;
                                        }
                                        // to enter shiru cafe
                                        if(x>=565 && x<=585 && y-speed>=750){
                                                y-=speed;
                                        }
                                        // to enter amul
                                        if(x>=700 && x<=715 && y-speed>=750){
                                                y-=speed;
                                        }
                                        // to enter nesacfe
                                        if(x>=850 && x<=865 && y-speed>=750){
                                                y-=speed;
                                        }
                                        if(purchasedJetPack && y-speed>=0){
                                                y-=speed;
                                        }

                                }
                                if(keyPress == KEY_PRESS_DOWN){
                                        if(x>=870 && x<=890 && y+speed<=200){
                                                y+=speed;
                                        }
                                        if(x>=520 && x<=540 && y+speed<=200){
                                                y+=speed;
                                        }
                                        if(x>=330 && x<=350 && y+speed<=170){
                                                y+=speed;
                                        }
                                        if(x>=120 && x<=145 && y+speed<=170){
                                                y+=speed;
                                        }
                                        if(y+speed<=190 && x<=1000 && x>=0){
                                                y+=speed;
                                        }
                                        if(x<=255 && x>=230 && y+speed<=990){
                                                y+=speed;
                                        }
                                        if(x<=995 && x>=970 && y+speed<=990 && y>=650){
                                                y+=speed;
                                        }

                                        if(x<=680 && x>=650 && y+speed<=557){
                                                y+=speed;
                                        }

                                        if(x<=600 && x>=575 && y+speed<=690 && y>=500){
                                                y+=speed;
                                        }
                                        if(x<=800 && x>=760 && y+speed<=470 ){
                                                y+=speed;
                                        }
                                        if(x>=355 && x<=380 && y+speed<=350 && y>=250){
                                                y+=speed;
                                        }

                                        if(x>=455 && x<=480 && y+speed<=350 && y>=250){
                                                y+=speed;
                                        }
                                        if(x>=565 && x<=585 && y+speed<=780 && y>700){
                                                y+=speed;
                                        }

                                        if(x>=700 && x<=715 && y+speed<=780){
                                                y+=speed;
                                        }
                                        if(x>=850 && x<=865 && y+speed<=780 && y>=700){
                                                y+=speed;
                                        }
                                        if(purchasedJetPack && y+speed<=SCREEN_HEIGHT){
                                                y+=speed;
                                        }
                                }
                                if(keyPress == KEY_PRESS_LEFT){
                                        if(y>=335 && y<=350 &&  x-speed>=760){
                                                x-=speed;
                                        }
                                        if(y>=160 && y<=190 &&  x-speed>=0){
                                                x-=speed;
                                        }
                                        if(970<=y && y<=990 && x-speed>=230){
                                                x-=speed;
                                        }
                                        if(y>=740 && y<=760 && x-speed>=230){
                                                x-=speed;
                                        }
                                        if(y>=295 && y<=325 && x-speed>=130){
                                                x-=speed;
                                        }
                                        if(y>=480 && y<=497 && x-speed>=225){
                                                x-=speed;
                                        }

                                        if(y>=543 && y<=560 && x-speed>=575){
                                                x-=speed;
                                        }

                                        if(y>=543 && y<=560 && x-speed>=130 && x<400){
                                                x-=speed;
                                        }
                                        if(y>=785 && y<=800 && x-speed>=160 && x<400){
                                                x-=speed;
                                        }
                                        if(y>=875 && y<=895 && x-speed>=160 && x<400){
                                                x-=speed;
                                        }
                                        if(y>=835 && y<=850 && x-speed>=980 && x>700){
                                                x-=speed;
                                        }
                                        if(purchasedJetPack && x-speed>=0){
                                                x-=speed;
                                        }

                                }
                                if(keyPress == KEY_PRESS_RIGHT){
                                        if(335<=y && y<=350 && x+speed<=820 && x>=500){
                                                x+=speed;
                                        }
                                        if(160<=y && y<=190 && x+speed<=1000){
                                                x+=speed;
                                        }
                                        if(970<=y && y<=990 && x+speed<=1000){
                                                x+=speed;
                                        }
                                        if(y>=740 && y<=760 && x+speed<=995){
                                                x+=speed;
                                        }
                                        if(y>=295 && y<=325 && x+speed<=787){
                                                x+=speed;
                                        }
                                        if(y>=480 && y<=497 && x+speed<=672){
                                                x+=speed;
                                        }
                                        if(y>=543 && y<=560 && x+speed<=672 && x>400){
                                                x+=speed;
                                        }
                                        if(y>=543 && y<=560 && x+speed<=265){
                                                x+=speed;
                                        }
                                        if(y>=785 && y<=800 && x+speed<=250 && x<400){
                                                x+=speed;
                                        }
                                        if(y>=875 && y<=895 && x+speed<=250 && x<400){
                                                x+=speed;
                                        }

                                        if(y>=835 && y<=850 && x+speed<=1040 && x>700){
                                                x+=speed;
                                        }
                                        if(purchasedJetPack && x+speed<=SCREEN_WIDTH){
                                                x+=speed;
                                        }
                                }
                        }
                        else if(!inMain){
                                  if (keyPress ==KEY_PRESS_UP){
                                        if(y-speed>=0){
                                                y-=speed;
                                        }
                                  }
                                  if(keyPress == KEY_PRESS_DOWN){
                                        if(y+speed<=SCREEN_HEIGHT){
                                                y+=speed;
                                        }
                                  }
                                  if(keyPress == KEY_PRESS_RIGHT){
                                        if(x+speed<=SCREEN_WIDTH){
                                                x+=speed;
                                        }
                                  }
                                  if(keyPress == KEY_PRESS_LEFT){
                                        if(x-speed>=0){
                                                x-=speed;;
                                        }
                                  }
                        }
                

        }

        

        void enter(){
                // enter into satpura building
                                // satpura                                     zanskar                             vidyanchal                            satpura                                   girnar and udaigiri                      nilgiri                                  karakoram                                         aravali                                jwalamukhi                            kumaon
                if (!takenYulu && inMain && ((x>=740 && x<=820 && 455<=y && y<=480) )){
                    playaudio(musenter) ;
                        enterHostel = true;
                        lastx = x;
                        purchasedJetPack = false;
                        lasty = y;
                        x = 0.1*SCREEN_WIDTH;
                        y = 0.4*SCREEN_HEIGHT;
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
                // exit from satpura building

                else if(enterHostel && x>=(int)(0.04*SCREEN_WIDTH) && x<=(int)(0.12*SCREEN_WIDTH) && y<=(int)(0.47*SCREEN_HEIGHT) && y>=(int)(0.36*SCREEN_HEIGHT)){
                    playaudio(musenter) ;
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
                // play table tennis in Satpura
                else if(enterHostel && x>=(int)(0.23*SCREEN_WIDTH) && x<=(int)(0.34*SCREEN_WIDTH) && y<=(int)(0.77*SCREEN_HEIGHT) && y>=(int)(0.67*SCREEN_HEIGHT)){
                        energy-=10;

                        temp2Clip = 0;
                        if(energy<=0){
                                hospitalize();
                        }
                        //health = min(100,health+10);
                        happiness = min(100,happiness+10);
                }
                // eating mess food
                else if(enterHostel && x>=(int)(0.57*SCREEN_WIDTH) && x<=(int)(0.67*SCREEN_WIDTH) &&
                        y<=(int)(0.8*SCREEN_HEIGHT) && y>=(int)(0.64*SCREEN_HEIGHT)){
                    playaudio(museating);
                    energy=min(energy+10,100);
                    happiness = max(happiness-5, 0) ;
                        temp3Clip = 0;
                    
                }

                // sleeping
                else if(enterHostel && x>=(int)(0.54*SCREEN_WIDTH) && x<=(int)(0.77*SCREEN_WIDTH) && y<=(int)(0.23*SCREEN_HEIGHT) && y>=(int)(0.01*SCREEN_HEIGHT)){
                    playaudio(mussnoring);
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
                        x = (int)(0.6*SCREEN_WIDTH);
                        y = (int)(0.2*SCREEN_HEIGHT);
                        Mix_HaltMusic() ;
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
                else if(!takenYulu && inMain && x>=120 && x<=220 && y>=540 && y<=570){
                        inLargeGround = true;
                        purchasedJetPack = false;
                        inMain = false;
                        enterHostel = false;
                        x = 1300;
                        y = 500;
                    playaudio(musenter) ;
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
                    playaudio(musenter) ;
                    
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
                    playaudio(mussport) ;

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
                    playaudio(mussport) ;
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
                    playaudio(mussport) ;
                }

                // entering tennis court
                else if(!takenYulu && inMain && y>=290 && y<=315 && x>=350 && x<=370){
                        inTennisCourt = true;
                        purchasedJetPack = false;
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
                    playaudio(musenter) ;
                        
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
                    playaudio(mussport) ;
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
                        x = 365;
                        y = 310;
                    playaudio(musenter) ;
                }

                // enter volleyBall Court
                else if(!takenYulu && inMain && y>=0.3*SCREEN_HEIGHT - 20 && y<=0.33*SCREEN_WIDTH +10  && x>=498 && x<=510){
                        inTennisCourt = false;
                        purchasedJetPack = false;
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
                    playaudio(musenter) ;
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
                    playaudio(mussport) ;
                }

                // exit volley court
                else if (inVolleyCourt && x>=1350 && x<=1490 && y<=520 && y>=450){
                        inMain = true;
                        enterHostel = false;
                        inTennisCourt = false;
                        inVolleyCourt = false;
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
                    playaudio(musenter) ;
                    
                }

                // enter lhc
                else if(!takenYulu && inMain && y>=870 && y<=890 && x>=140 && x<=220){
                        inLHC = true;
                        purchasedJetPack = false;
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
                    playaudio(musenter) ;
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
                    playaudio(musenter) ;
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
                    playaudio(musenter) ;
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
                    playaudio(musenter) ;
                }
            // enter into restaurants
        
                else if (!takenYulu && !enterRestaurant && (x>=(SCREEN_WIDTH / 22+120+130) && x<=(SCREEN_WIDTH / 22+150+130) && y<=(SCREEN_HEIGHT / 22+425 + (SCREEN_HEIGHT / 20)) && y>=(SCREEN_HEIGHT / 22+425) )                                                               //Masala Mix
                && inMain){
                        purchasedJetPack = false;
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
                        playaudio(musenter) ;
                }

                else if (
                (!takenYulu && !enterRestaurant && x>=(SCREEN_WIDTH / 22+95+160+100) && x<=(SCREEN_WIDTH / 22+95+185+100) && y<=(SCREEN_HEIGHT / 22+425 + (SCREEN_HEIGHT / 20)) && y>=SCREEN_HEIGHT / 22+425    )       //Rajdhani
                && inMain){
                        purchasedJetPack = false;
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
                        playaudio(musenter) ;
                }

                else if (!takenYulu && !enterRestaurant &&
                (x>= SCREEN_WIDTH / 22+95+255+100 && x<=( SCREEN_WIDTH / 22+95+285+100) && y<=(SCREEN_HEIGHT / 22+425 + (SCREEN_HEIGHT / 20)) && y>=SCREEN_HEIGHT / 22+425)   // Chaayos
                && inMain){
                        purchasedJetPack = false;
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
                        playaudio(musenter) ;
                }
                
               else if (!takenYulu && !enterRestaurant&&
                        // enter shiru
                ( x>= SCREEN_WIDTH / 22+500 && x<=( SCREEN_WIDTH / 22+450 + (SCREEN_WIDTH / 18)) && y<=(SCREEN_HEIGHT / 22+695+ (SCREEN_HEIGHT / 18)) && y>=SCREEN_HEIGHT / 22+695  ) //Shiru Cafe
                && inMain){
                        purchasedJetPack = false;
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
                        playaudio(musenter) ;
                }


                else if (!takenYulu && !enterRestaurant&&
                        // enter amul
                (x>= SCREEN_WIDTH / 22+630 && x<=( SCREEN_WIDTH / 22+580 + (SCREEN_WIDTH / 18)) && y<=(SCREEN_HEIGHT / 22+695 + (SCREEN_HEIGHT / 18)) && y>=SCREEN_HEIGHT / 22+695 )  //Amul
                && inMain){
                        purchasedJetPack = false;
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
                        playaudio(musenter) ;
                }


                else if (!takenYulu && !enterRestaurant&&
                (x>= SCREEN_WIDTH / 22+780 && x<=( SCREEN_WIDTH / 22+720 + (SCREEN_WIDTH / 18)) && y<=(SCREEN_HEIGHT / 22+695 + (SCREEN_HEIGHT / 18)) && y>=SCREEN_HEIGHT / 22+695)   //Nescafe
                && inMain){
                        purchasedJetPack = false;
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
                        playaudio(musenter) ;
                }


                else if (!takenYulu && !enterRestaurant&&
                (x>= SCREEN_WIDTH / 22+880 && x<=( SCREEN_WIDTH / 22+880 + (SCREEN_WIDTH / 15)) && y<=(SCREEN_HEIGHT / 22+690 + (SCREEN_HEIGHT / 8)) && y>=SCREEN_HEIGHT / 22+780 )  //CCD
                && inMain){
                        purchasedJetPack = false;
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
                        playaudio(musenter) ;
                }


                else if (!takenYulu && !enterRestaurant&&
                (x>= SCREEN_WIDTH / 22+80 && x<=( SCREEN_WIDTH / 22 + 110) && y<=(SCREEN_HEIGHT / 22+590 + (SCREEN_HEIGHT / 6)) && y>=SCREEN_HEIGHT / 22+725)  //Staff Canteen
                && inMain){
                        purchasedJetPack = false;
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
                        playaudio(musenter) ;
                }


                else if (!takenYulu && !enterRestaurant&&
                        // enter dilli16
                (x>= SCREEN_WIDTH / 22+95+130+40+160 && x<=( SCREEN_WIDTH / 22+95+130+40+160 + (SCREEN_WIDTH / 15)) && y<=(SCREEN_HEIGHT / 22+134 + (SCREEN_HEIGHT / 20)) && y>=SCREEN_HEIGHT / 22+134 ) //Dilli-16
                && inMain){
                        purchasedJetPack = false;
                    playaudio(musenter) ;
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
                        purchasedJetPack = false;
                    playaudio(musenter) ;
                    enterRestaurant = false;
                        enterMasalaMix = false;
                        inMain = true;
                        x = SCREEN_WIDTH / 22+95+130 + 35;
                        y = SCREEN_HEIGHT / 22+425+ 10 ;
                        
                }

                else if (x>=SCREEN_WIDTH*0.75 && x<=0.9*SCREEN_WIDTH && y>=0.09*SCREEN_HEIGHT && y<=0.21*SCREEN_HEIGHT
                && enterRajdhani){
                        purchasedJetPack = false;
                    playaudio(musenter) ;
                    enterRestaurant = false;
                        enterRajdhani = false;
                        inMain = true;
                        x = (SCREEN_WIDTH / 22+95+130+100 + 35);
                        y = SCREEN_HEIGHT / 22+425 + 10 ;
                        
                }

                else if (x>=SCREEN_WIDTH*0.75 && x<=0.9*SCREEN_WIDTH && y>=0.09*SCREEN_HEIGHT && y<=0.21*SCREEN_HEIGHT
                && enterChaayos){
                        purchasedJetPack = false;
                    playaudio(musenter) ;
                    enterRestaurant = false;
                        enterChaayos = false;
                        inMain = true;
                        x = SCREEN_WIDTH / 22+95+130+200 + 35;
                        y = SCREEN_HEIGHT / 22+425 + 10 ;
                        
                }

                else if (x>=SCREEN_WIDTH*0.75 && x<=0.9*SCREEN_WIDTH && y>=0.09*SCREEN_HEIGHT && y<=0.21*SCREEN_HEIGHT
                && enterShiru){
                        purchasedJetPack = false;
                    playaudio(musenter) ;
                    enterRestaurant = false;
                        enterShiru = false;
                        inMain = true;
                        x = SCREEN_WIDTH / 22+480 + 20;
                        y = SCREEN_HEIGHT / 22+695 + 5 ;
                        
                }

                else if (x>=SCREEN_WIDTH*0.75 && x<=0.9*SCREEN_WIDTH && y>=0.09*SCREEN_HEIGHT && y<=0.21*SCREEN_HEIGHT
                && enterAmul){
                        purchasedJetPack = false;
                    playaudio(musenter) ;
                    enterRestaurant = false;
                        enterAmul = false;
                        inMain = true;
                        x = SCREEN_WIDTH / 22+610 + 20;
                        y = SCREEN_HEIGHT / 22+695 + 5 ;
                        
                }

                else if (x>=SCREEN_WIDTH*0.75 && x<=0.9*SCREEN_WIDTH && y>=0.09*SCREEN_HEIGHT && y<=0.21*SCREEN_HEIGHT
                && enterNescafe){
                        purchasedJetPack = false;
                    playaudio(musenter) ;
                    enterRestaurant = false;
                        enterNescafe = false;
                        inMain = true;
                        x = SCREEN_WIDTH / 22+760 + 20;
                        y = SCREEN_HEIGHT / 22+695+ 5 ;
                        
                }


                else if (x>=SCREEN_WIDTH*0.75 && x<=0.9*SCREEN_WIDTH && y>=0.09*SCREEN_HEIGHT && y<=0.21*SCREEN_HEIGHT
                && enterCCD){
                        purchasedJetPack = false;
                        enterRestaurant = false;
                        enterCCD = false;
                        inMain = true;
                        x = SCREEN_WIDTH / 22+860 + 60;
                        y = SCREEN_HEIGHT / 22+760+ 47 ;
                        playaudio(musenter) ;
                }


                else if (x>=SCREEN_WIDTH*0.75 && x<=0.9*SCREEN_WIDTH && y>=0.09*SCREEN_HEIGHT && y<=0.21*SCREEN_HEIGHT
                && enterStaffCanteen){
                        purchasedJetPack = false;
                    playaudio(musenter) ;
                    enterRestaurant = false;
                        enterStaffCanteen = false;
                        inMain = true;
                        x = SCREEN_WIDTH / 22+60 + 30;
                        y = SCREEN_HEIGHT / 22+735 + 14;
                        
                }


                else if (x>=SCREEN_WIDTH*0.75 && x<=0.9*SCREEN_WIDTH && y>=0.09*SCREEN_HEIGHT && y<=0.21*SCREEN_HEIGHT
                && enterDilli16){
                        purchasedJetPack = false;
                    playaudio(musenter) ;
                    enterRestaurant = false;
                        enterDilli16 = false;
                        inMain = true;
                        x = SCREEN_WIDTH / 22+95+130+40+160 + 40;
                        y = SCREEN_HEIGHT / 22+134 + 13;
                        
                }


                //Counter
                else if(enterRestaurant && x>=SCREEN_WIDTH*0.03 && x<=0.68*SCREEN_WIDTH && y>=0.2*SCREEN_HEIGHT && y<=0.3*SCREEN_HEIGHT){
                        
                        if(money<20){
                                insufficientMoney = true;
                        }
                        else{
                            playaudio(museating) ;
                        happiness = min(happiness+10, 100);
                        health-=10;
                        if(health<=0){
                                hospitalize();
                        }
                        else{
                            energy=min(energy+10, 100);
                        money-=20;
                            temp12Clip = 0;
                            x = 0.7*SCREEN_WIDTH;
                            y = 0.42*SCREEN_HEIGHT-10;
                        }
                        }
                        
                }

        
                

                //SAC



                // enter into SAC

                else if (!takenYulu && x>=(0) && x<=SCREEN_WIDTH / 10 && y<=SCREEN_HEIGHT / 8  + SCREEN_HEIGHT / 22+220  && y>=SCREEN_HEIGHT / 22+220 && inMain){
                        enterSAC = true;
                        purchasedJetPack = false;
                        x = SCREEN_WIDTH*0.09;
                        y = 0.75*SCREEN_HEIGHT;
                        inMain = false;
                        playaudio(musenter) ;
                }
                // exit from SAC

                else if(enterSAC && x>=SCREEN_WIDTH*0.06 && x<=0.24*SCREEN_WIDTH && y>=0.72*SCREEN_HEIGHT && y<=0.93*SCREEN_HEIGHT){
                        enterSAC = false;
                        inMain = true;
                        x = SCREEN_WIDTH / 20+60;
                        y = SCREEN_HEIGHT / 22+265 ;
                        playaudio(musenter) ;
                }

                //Music Room

                else if(enterSAC && x>=SCREEN_WIDTH*0.14 && x<=0.34*SCREEN_WIDTH && y>=0.34*SCREEN_HEIGHT && y<=0.52*SCREEN_HEIGHT){
                        
                        happiness = min(100,happiness+10);
                        energy-=5;
                        if(energy<=0){
                                hospitalize();
                        }
                        playaudio(musmusic) ;

                        
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
                        playaudio(musclick) ;

                        
                }


                //Badminton Court

                else if(enterSAC && x>=SCREEN_WIDTH*0.16 && x<=0.53*SCREEN_WIDTH && y>=0*SCREEN_HEIGHT && y<=0.18*SCREEN_HEIGHT){
                        temp10Clip = 0;
                        happiness = min(100,happiness+10);
                        health=min(health+10, 100);
                        energy-=10;
                        if(energy<=0){
                                hospitalize();
                        }
                        playaudio(musclick) ;

                        
                }

                // enter OAT

                else if(enterSAC && x>=0.49*SCREEN_WIDTH && x<=0.85*SCREEN_WIDTH && y>=0.43*SCREEN_HEIGHT && y<=0.89*SCREEN_HEIGHT){
                        inOAT = true;
                        playaudio(musdisco) ;
                        purchasedJetPack = false;
                        //cout<<"PLAYER1ENTEREDOAT\n";
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

                //exit OAT
                else if(inOAT){
                        inOAT = false;
                        enterSAC = true;
                        inMain = false;
                        
                        Mix_HaltMusic() ;
                        x = (int)(0.66*SCREEN_WIDTH);
                        y = (int)(0.66*(SCREEN_HEIGHT));
                        enterHostel = false;
                        inLargeGround = false;
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
                }





                //Library



                // enter into Library

                else if (!takenYulu && y<=990  && y>=970 && x>=700 && x<=800&& inMain){          // SUBSTITUTE ACCURATE COORDINATES ACCORDING TO INTERROAD POSITION OF LIBRARY
                    playaudio(musenter);
                        enterLibrary = true;
                        x = SCREEN_WIDTH*0.04;
                        y = 0.58*SCREEN_HEIGHT;
                        inMain = false;
                        purchasedJetPack = false;

                }
                // exit from Library

                else if(enterLibrary && x>=1350 && x<=1490 && y<=520 && y>=450){
                    playaudio(musenter) ;
                    enterLibrary = false;
                        inMain = true;
                        x = 750;                  //ACCORDINGLY SET COORDINATES OF LIBRARY INTERROAD
                        y = 980 ;
                    
                }

                //Chair
                // change view to study
                else if(enterLibrary && x>=0.6*SCREEN_WIDTH && x<=0.8*SCREEN_WIDTH && y>=0.18*SCREEN_HEIGHT && y<=0.43*SCREEN_HEIGHT){
                        purchasedJetPack = false;
                        enterLibrary = false;
                        isStudying = true;
                

                }
                // studying in library
                else if(isStudying){
                        enterLibrary = true;
                        isStudying = false;
                }

                // enter CSC

                else if(inMain && x>=980 && x<=1010 && y>=970 && y<=1000){
                        inCSC = true;
                        inMain = false;
                }
                else if(inCSC){
                        inMain = true;
                        inCSC = false;
                        x = 990;
                        y = 990;
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
                        if(hospitalized)
                            temp2++;
                        if(temp2==3){
                            temp2 = 0;
                            //cout<<"making hospitalized as true false\n";
                            hospitalized = false;
                        }
                        if(purchasedJetPack){
                                temp4++;
                        }
                        if(temp4==15){
                                temp4=0;
                                purchasedJetPack = false;
                                x = beforeJetx;
                                y = beforeJety;
                        }

                    }

            }


        void changeYulu(){
                // initially did not have yulu
                if (money>0){

                        if(x>=138 && x<=215 && y>=300 && y<=325){
                           if(!takenYulu){
                                takenYulu = true;
                                speed+=1;
                               playaudio(musyulu) ;
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
                               playaudio(musyulu) ;
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
                               playaudio(musyulu) ;
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
                               playaudio(musyulu) ;
                           }
                           else{   // already had yulu now leaving it
                                takenYulu = false;
                                speed-=1;
                           }
                        }

                        if(x>=947 && x<=994 && y<=195 && y>=160){
                           if(!takenYulu){
                                takenYulu = true;
                                speed+=1;
                               playaudio(musyulu) ;
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
                               playaudio(musyulu) ;
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
                               playaudio(musyulu) ;
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

        void changeJetPack(){
                if(!purchasedJetPack){
                        if(money>=60){
                                 playaudio(musjetpack) ;
                                 money-=60;
                                purchasedJetPack = true;
                                beforeJetx = x;
                                beforeJety = y;
                        }
                        else{
                                insufficientMoney = true;
                        }
                }
        }

        void renderPlayer(){
                SDL_Rect player1 = {x,y,30,30};
                if(lastStepDirection==0 && !takenYulu && !purchasedJetPack)
                    SDL_RenderCopy(gRenderer,colorTexFront,NULL,&player1);
                else if(lastStepDirection==1 && !takenYulu && !purchasedJetPack)
                    SDL_RenderCopy(gRenderer,colorTexBack,NULL,&player1);
                else if(lastStepDirection==2 && !takenYulu && !purchasedJetPack)
                    SDL_RenderCopy(gRenderer,colorTexLeft,NULL,&player1);
                else if(lastStepDirection==3 && !takenYulu && !purchasedJetPack)
                    SDL_RenderCopy(gRenderer,colorTexRight,NULL,&player1);



                else if(lastStepDirection==0 && takenYulu && !purchasedJetPack)
                    SDL_RenderCopy(gRenderer,cycleTexFront,NULL,&player1);
                else if(lastStepDirection==1 && takenYulu && !purchasedJetPack)
                    SDL_RenderCopy(gRenderer,cycleTexBack,NULL,&player1);
                else if(lastStepDirection==2 && takenYulu && !purchasedJetPack)
                    SDL_RenderCopy(gRenderer,cycleTexLeft,NULL,&player1);
                else if(lastStepDirection==3 && takenYulu && !purchasedJetPack)
                    SDL_RenderCopy(gRenderer,cycleTexRight,NULL,&player1);

                else if(lastStepDirection==0 && purchasedJetPack)
                    SDL_RenderCopy(gRenderer,jetPackTexFront,NULL,&player1);
                else if(lastStepDirection==1 && purchasedJetPack)
                    SDL_RenderCopy(gRenderer,jetPackTexBack,NULL,&player1);
                else if(lastStepDirection==2 && purchasedJetPack)
                    SDL_RenderCopy(gRenderer,jetPackTexLeft,NULL,&player1);
                else if(lastStepDirection==3 && purchasedJetPack)
                    SDL_RenderCopy(gRenderer,jetPackTexRight,NULL,&player1);
        }

};



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
                
            
            // Inilialize SDL_mixer , exit if fail
            if( SDL_Init(SDL_INIT_AUDIO) < 0 ) exit(1);
            // Setup audio mode
            Mix_OpenAudio(22050,AUDIO_S16SYS,2,640);
            //Mix_Music *musenter , *musclick, *musmusic ;  // Background Music
            Mix_Chunk *wav , *wav2 ;  // For Sounds

            
            musenter = Mix_LoadMUS("/Users/eshan/Downloads/enter-sound.wav");
            musclick = Mix_LoadMUS("/Users/eshan/Downloads/click-sound.wav");
            musmusic = Mix_LoadMUS("/Users/eshan/Desktop/COP-290-TASK-2-master/sounds/music-zapsplat-game-music-action-fun-funky-electro-disco-023_yKJBjSw4.wav");
            musyulu = Mix_LoadMUS("/Users/eshan/Desktop/yulusound.wav");
            mussport = Mix_LoadMUS("/Users/eshan/Desktop/sportsound.wav");
            muswon = Mix_LoadMUS("/Users/eshan/Desktop/wonsound.wav");
            muslose = Mix_LoadMUS("/Users/eshan/Desktop/losesound.wav");
            musinsufficientmoney = Mix_LoadMUS("/Users/eshan/Desktop/insufficientmoney.wav");
            museating = Mix_LoadMUS("/Users/eshan/Desktop/eatingsound.wav");
            muspeacock = Mix_LoadMUS("/Users/eshan/Main/OneDrive - IIT Delhi 2/Eshan/Sem-4/COP290/Task-2/sdl2-starter/src/sounds/peacocksound.wav");
            musdisco = Mix_LoadMUS("/Users/eshan/Main/OneDrive - IIT Delhi 2/Eshan/Sem-4/COP290/Task-2/sdl2-starter/src/sounds/discosound.wav");
            mussnoring = Mix_LoadMUS("/Users/eshan/Main/OneDrive - IIT Delhi 2/Eshan/Sem-4/COP290/Task-2/sdl2-starter/src/sounds/snoringsound.wav");
            musjetpack = Mix_LoadMUS("/Users/eshan/Downloads/jetpacksound.wav");


            
            //mus2 = Mix_LoadMUS("./mixer/aria.mp3");
            //wav = Mix_LoadWAV("./mixer/po_p2k.wav");
            //wav2 = Mix_LoadWAV("./mixer/start.wav");
            
            
            
            SDL_Texture*jetTopTex = loadFromFile("jetpacktop.png");
            
            //oat dancing tex
            
            SDL_Texture* oatinsideTex1 = loadFromFile("oatinside1.png");
            SDL_Texture* oatinsideTex2 = loadFromFile("oatinside2.png");
            SDL_Texture* oatinsideTex3 = loadFromFile("oatinside3.png");
            // hostel textures
            SDL_Texture* hospitalizeTex = loadFromFile("hospitalized.png");
                SDL_Texture* tileTex = loadFromFile("tile.png");
                SDL_Texture* ttableTex = loadFromFile("tabletennis.png");
                SDL_Texture* messTex = loadFromFile("mess.png");
                SDL_Texture* grassTex = loadFromFile("grass.png");
                SDL_Texture* roomTex = loadFromFile("room.png");
                SDL_Texture* restaurantTex = loadFromFile("pizzaframe5.png");
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
                SDL_Texture* largeGroundTex = loadFromFile("largegroundOuter.png");
                SDL_Texture* gtree1Tex = loadFromFile("tree-top.png");
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

                SDL_Texture* catTex1 = loadFromFile("catframe1.png");
                SDL_Texture* catTex2 = loadFromFile("catframe2.png");
                SDL_Texture* catTex3 = loadFromFile("catframe3.png");
                SDL_Texture* startTex = loadFromFile("start-page.png");
                SDL_Texture* waitTex = loadFromFile("waiting.png");
            
                SDL_Texture* youwonTex = loadFromFile("youwin.png");
                SDL_Texture* youlostTex = loadFromFile("youlose.png");
            
                SDL_Texture* bookiconTex = loadFromFile("bookicon.png");
                SDL_Texture* hearticonTex ;
                SDL_Texture* hearticon1Tex = loadFromFile("hearticon1.png");
                SDL_Texture* hearticon2Tex = loadFromFile("hearticon2.png");
                SDL_Texture* hearticon3Tex = loadFromFile("hearticon3.png");
                SDL_Texture* hearticon4Tex = loadFromFile("hearticon4.png");
                SDL_Texture* hearticon5Tex = loadFromFile("hearticon5.png");
            
            
            
                SDL_Texture* moneyiconTex = loadFromFile("moneyicon.png");
                SDL_Texture* happinessiconTex;
                SDL_Texture* happinessicon1Tex = loadFromFile("happyfaceicon1.png");
                SDL_Texture* happinessicon2Tex = loadFromFile("happyfaceicon2.png");
                SDL_Texture* happinessicon3Tex = loadFromFile("happyfaceicon3.png");
                SDL_Texture* happinessicon4Tex = loadFromFile("happyfaceicon4.png");
                SDL_Texture* happinessicon5Tex = loadFromFile("happyfaceicon5.png");
                
                SDL_Texture* energyiconTex;
                SDL_Texture* energyicon1Tex = loadFromFile("energyicon1.png");
                SDL_Texture* energyicon2Tex = loadFromFile("energyicon2.png");
                SDL_Texture* energyicon3Tex = loadFromFile("energyicon3.png");
                SDL_Texture* energyicon4Tex = loadFromFile("energyicon4.png");
                SDL_Texture* energyicon5Tex = loadFromFile("energyicon5.png");
            
            
            
            SDL_Texture* pizzaframeTex1 = loadFromFile("pizzaframe1.png");
            SDL_Texture* pizzaframeTex2 = loadFromFile("pizzaframe2.png");
            SDL_Texture* pizzaframeTex3 = loadFromFile("pizzaframe3.png");
            SDL_Texture* pizzaframeTex4 = loadFromFile("pizzaframe4.png");
            
            
            SDL_Texture* peacockframeTex1 = loadFromFile("peacockframe1.png");
                            SDL_Texture* peacockframeTex2 = loadFromFile("peacockframe2.png");
                            SDL_Texture* peacockframeTex3 = loadFromFile("peacockframe3.png");
                            SDL_Texture* peacockframeTex4 = loadFromFile("peacockframe4.png");
                            SDL_Texture* peacockframeTex5 = loadFromFile("peacockframe5.png");

            SDL_Texture* cscInsideTex = loadFromFile("cscinside.png");

            pair<int,int> startlocation = startLocations[generateRandomPoint(5).first%5];
                Player player1 = Player(startlocation.first,startlocation.second,"purple");
                Player player2 = Player(60,175,"pink");
                bool quit = false;

                SDL_Event e;


                while(!quit){
                        
                    if(player1.happiness>=70 && player1.knowledge>=70 && player1.health>=60){
                        
                
                        player1.won = true;
                        player2.lost = true;
                    }
                    
                    
                    
                    
                    // cout<<player1.lastStepDirection<<"\n";
                    
                    

                        // player1 is bankerupt
                        if(player1.money ==0 && !player1.bankrupt){
                            if (player1.takenYulu){
                                player1.speed-=1;
                            }
                                player1.takenYulu = false;
                                
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
                                if(player1.isReady){
                                    buff[35] = '1';
                                    
                                }
                                else{
                                    buff[35]='0';
                                    }
                                if(player1.won){
                                    buff[36] = '1';
                                    player2.lost = true;

                                }
                                else{
                                    buff[36] = '0';
                                }
                                if(player1.lost){
                                    buff[37] = '1';
                                    player2.won = true;
                                }
                                else{
                                    buff[37] = '0';
                                }
                                if(player1.takenYulu){
                                        buff[38]='1';
                                }
                                else{
                                        buff[38]='0';
                                }
                                if(player1.purchasedJetPack){
                                        buff[39]='1';
                                }
                                else{
                                        buff[39]='0';
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
                    vector<pair<int,int>> startLocations = {{65,175},{245,310},{980,745},{665,475},{SCREEN_WIDTH-600,175}};
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
                                
                                if(buff[35]=='1'){
                                        player2.isReady = true;
                                }
                                else{
                                        player2.isReady = false;
                                }
                                if(buff[36]=='1'){
                                        player2.won = true;
                                        player1.lost = true;
                                }
                                else{
                                        player2.won = false;
                                }
                                if(buff[37]=='1'){
                                        player2.lost = true;
                                        player1.won = true;
                                }
                                else{
                                        player2.lost = false;
                                }
                                if(buff[38]=='1'){
                                        player2.takenYulu = true;
                                }
                                else{
                                        player2.takenYulu = false;
                                }
                                if(buff[39]=='1'){
                                        player2.purchasedJetPack = true;
                                }
                                else{
                                        player2.purchasedJetPack = false;
                                }
                    //cout<<player1.x<<" "<<player1.y<<"\n";
                    //cout<<player1.won<<" "<<player1.isReady<<"\n";
                    if(player1.isReady && player2.isReady && !player1.won && !player1.lost && !player1.inMain && !player1.enterHostel && !player1.inLargeGround && !player1.inTennisCourt && !player1.inVolleyCourt && !player1.inLHC && !player1.inLHC108 && !player1.inLHC114 && !player1.inLHC325 && !player1.enterSAC && !player1.enterRestaurant && !player1.enterMasalaMix && !player1.enterRajdhani && !player1.enterRestaurant && !player1.enterChaayos && !player1.enterShiru && !player1.enterAmul && !player1.enterNescafe && !player1.enterCCD && !player1.enterStaffCanteen && !player1.enterDilli16 && !player1.enterLibrary && !player1.isSleeping && !player1.isStudying && !player1.inOAT && !player1.inCSC){
                        player1.inMain = true;
                        player2.inMain = true;
                                }
                    if(!player1.isReady && !player1.won && !player1.lost){
                                                    while( SDL_PollEvent( &e ) != 0 )
                                                            {
                                                                    //User requests quit
                                                                    if( e.type == SDL_QUIT )
                                                                    {
                                                                            quit = true;
                                                                    }
                                                                    else if(e.type == SDL_MOUSEBUTTONDOWN){
                                                                            SDL_GetMouseState(&mousex,&mousey);
                                                                            if(mousex>=(int)(0.36*SCREEN_WIDTH) && mousex<=(int)(0.63*SCREEN_WIDTH) && mousey>=(int)(0.87*SCREEN_HEIGHT) && mousey<=(int)(0.94*SCREEN_HEIGHT)){
                                                                                    player1.isReady = true;
//                                                                                    if(player1.isReady && player2.isReady && !player1.won && !player1.lost){
//                                                                                        player1.inMain = true;
//                                                                                     }
                                                                            }
                                                                    }
                                                                    else if(e.type == SDL_KEYDOWN){
                                                                            switch(e.key.keysym.sym){
                                                                                    case SDLK_e:
                                                                                    player1.isReady = true;
//                                                                                    if(player1.isReady && player2.isReady && !player1.won && !player1.lost){
//                                                                                        player1.inMain = true;
//                                                                                     }
                                                                            }
                                                                    }


                                                            }
                                                            SDL_Rect startRect = {0,0,SCREEN_WIDTH,SCREEN_HEIGHT};
                                                            SDL_RenderCopy(gRenderer,startTex,NULL,&startRect);
                                }
            else if(!player2.isReady && player1.isReady){
                                SDL_Rect waitRect = {0,0,SCREEN_WIDTH,SCREEN_HEIGHT};
                                SDL_RenderCopy(gRenderer,waitTex,NULL,&waitRect);
                player1.won = false;
                player1.lost = false;
                player2.lost = false;
                player2.won = false;
                //cout<<"REACHED HERE AS WELL\n";
            }
            else if(player1.won){
                //cout<<"REACHED HERE\n";
                if(fwon==0){playaudio(muswon) ;}
                //cout<<fwon<<"\n";
                fwon=1 ;
                SDL_Rect p1won = {0,0,SCREEN_WIDTH,SCREEN_HEIGHT};
                                        SDL_RenderCopy(gRenderer,youwonTex,NULL,&p1won);
                player1.inMain = player1.enterHostel = player1.inLargeGround = player1.inTennisCourt = player1.inVolleyCourt = player1.inLHC = player1.inLHC108 = player1.inLHC114 = player1.takenYulu = player1.inLHC325 = player1.enterSAC = player1.enterRestaurant = player1.enterShiru = player1.enterAmul = player1.enterNescafe = player1.enterCCD = player1.enterStaffCanteen = player1.enterDilli16 = player1.enterLibrary = player1.isSleeping = player1.bankrupt = player1.isStudying = false;
                                        player1.lastStepDirection = 0;
                                        player1.health = 50;
                                        player1.energy = 100;
                                        player1.happiness = 50;
                                        player1.money = 50;
                                        player1.knowledge = 10;
                                        pair<int,int> newLocation = startLocations[generateRandomPoint(10).first%5];
                                        player1.x = newLocation.first;
                                        player1.y = newLocation.second;
                                        player1.speed = 15;
                                        player2.inMain = player2.enterHostel = player2.inLargeGround = player2.inTennisCourt = player2.inVolleyCourt = player2.inLHC = player2.inLHC108 =player2.takenYulu =  player2.inLHC114 = player2.inLHC325 = player2.enterSAC = player2.enterRestaurant = player2.enterShiru = player2.enterAmul = player2.enterNescafe = player2.enterCCD = player2.enterStaffCanteen = player2.enterDilli16 = player2.enterLibrary = player2.isSleeping = player2.bankrupt = player2.isStudying = false;
                                        player2.lost = true;
                                        player1.isReady = false;
                                        player2.isReady = false;
                                        running = false;
                                        hospitalized = false;
                                        notScolded  = true;
                                        hungry = true;
                                        insufficientMoney = false;
                                        temp = 0;
                                        temp2 = 0;
                                        k = 0;
                                        newC = 0;
                                        temp2Clip = 450;
                                        temp3Clip = 500;
                                        temp4Clip = 500;
                                        temp5Clip = 500;
                                        temp6Clip = 500;
                                        temp7Clip = 500;
                                        temp8Clip = 500;
                                        temp9Clip = 500;
                                        temp10Clip = 500;
                                        temp11Clip = 500;
                                        temp12Clip = 500;
                
                hospitalized = false;
                notScolded  = true;
                hungry = true;
                insufficientMoney = false;
                                        while( SDL_PollEvent( &e ) != 0 )
                                                        {
                                                                //User requests quit
                                                                if( e.type == SDL_QUIT )
                                                                {
                                                                        quit = true;
                                                                }
                                                                else if(e.type == SDL_MOUSEBUTTONDOWN){
                                                                        SDL_GetMouseState(&mousex,&mousey);
                                                                        if(mousex>=(int)(0.26*SCREEN_WIDTH) && mousex<=(int)(0.67*SCREEN_WIDTH) && mousey>=(int)(0.60*SCREEN_HEIGHT) && mousey<=(int)(0.73*SCREEN_HEIGHT)){
                                                                                player1.isReady = true;
                                                                                player1.won = false;
                                                                                fwon=0 ;
                                                                        }
                                                                }
                                                                else if(e.type == SDL_KEYDOWN){
                                                                        switch(e.key.keysym.sym){
                                                                                case SDLK_e:
                                                                                player1.isReady = true;
                                                                                player1.won = false;
                                                                                fwon=0;
                                                                        }
                                                                }


                                                        }


                                }
            
            else if(player1.lost){
                                        
                if(flose==0) {playaudio(muslose) ;}

                flose=1 ;
                
                
                SDL_Rect p1lost = {0,0,SCREEN_WIDTH,SCREEN_HEIGHT};
                                        SDL_RenderCopy(gRenderer,youlostTex,NULL,&p1lost);
                player1.inMain = player1.enterHostel = player1.inLargeGround = player1.inTennisCourt = player1.inVolleyCourt = player1.inLHC = player1.inLHC108 = player1.inLHC114 = player1.inLHC325 = player1.enterSAC = player1.enterRestaurant = player1.enterShiru = player1.enterAmul = player1.enterNescafe = player1.enterCCD = player1.enterStaffCanteen = player1.enterDilli16 = player1.enterLibrary = player1.isSleeping = player1.bankrupt  = player1.takenYulu= player1.isStudying = false;
                                        player1.lastStepDirection = 0;
                                        player1.health = 50;
                                        player1.energy = 100;
                                        player1.happiness = 50;
                                        player1.money = 50;
                                        player1.knowledge = 10;
                pair<int,int> newLocation = startLocations[generateRandomPoint(10).first%5];
                player1.x = newLocation.first;
                player1.y = newLocation.second;
                                        player1.speed = 15;
                                        player2.inMain = player2.enterHostel = player2.inLargeGround = player2.inTennisCourt = player2.inVolleyCourt = player2.inLHC = player2.inLHC108 = player2.takenYulu = player2.inLHC114 = player2.inLHC325 = player2.enterSAC = player2.enterRestaurant = player2.enterShiru = player2.enterAmul = player2.enterNescafe = player2.enterCCD = player2.enterStaffCanteen = player2.enterDilli16 = player2.enterLibrary = player2.isSleeping = player2.bankrupt = player2.isStudying = false;
                                        player2.won = true;
                                        player1.isReady = false;
                                        player2.isReady = false;
                                        running = false;
                                        hospitalized = false;
                                        notScolded  = true;
                                        hungry = true;
                                        insufficientMoney = false;
                                        temp = 0;
                                        temp2 = 0;
                                        k = 0;
                                        newC = 0;
                                        temp2Clip = 450;
                                        temp3Clip = 500;
                                        temp4Clip = 500;
                                        temp5Clip = 500;
                                        temp6Clip = 500;
                                        temp7Clip = 500;
                                        temp8Clip = 500;
                                        temp9Clip = 500;
                                        temp10Clip = 500;
                                        temp11Clip = 500;
                                        temp12Clip = 500;
                                        
                
                                        while( SDL_PollEvent( &e ) != 0 )
                                                        {
                                                                //User requests quit
                                                                if( e.type == SDL_QUIT )
                                                                {
                                                                        quit = true;
                                                                }
                                                                else if(e.type == SDL_MOUSEBUTTONDOWN){
                                                                        SDL_GetMouseState(&mousex,&mousey);
                                                                        if(mousex>=(int)(0.26*SCREEN_WIDTH) && mousex<=(int)(0.67*SCREEN_WIDTH) && mousey>=(int)(0.60*SCREEN_HEIGHT) && mousey<=(int)(0.73*SCREEN_HEIGHT)){
                                                                                player1.isReady = true;
                                                                                player1.lost = false;
                                                                                
                                                                        }
                                                                }
                                                                else if(e.type == SDL_KEYDOWN){
                                                                        switch(e.key.keysym.sym){
                                                                                case SDLK_e:
                                                                                player1.isReady = true;
                                                                                player1.lost = false;
                                                                                
                                                                        }
                                                                }


                                                        }
                                }
                    
                    
            else if(player1.inMain && player1.isReady && player2.isReady){
                    fwon=0;
                    flose=0;
                pair<int,int> p=generateRandomPoint(7) ;
                if(p.first>=900){
                    playaudio(muspeacock) ;
                }
                if(hospitalized){
                    //cout<<"hospitalized\n";
                    SDL_Rect hpt = {1000,0,400,400};
                    SDL_RenderCopy(gRenderer, hospitalizeTex, NULL, &hpt);
                }
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
                            
                            SDL_RenderCopy(gRenderer,gtree1Tex,NULL,&gtree2);
                            SDL_DestroyTexture(imageTexture);


                            SDL_Rect gtree3 = {8 , SCREEN_HEIGHT / 22+400+60, 100,100};
                            
                            SDL_RenderCopy(gRenderer,gtree1Tex,NULL,&gtree3);
                            SDL_DestroyTexture(imageTexture);

                            SDL_Rect gtree4 = {8 , SCREEN_HEIGHT / 22+400+90, 100,100};
                            SDL_RenderCopy(gRenderer,gtree1Tex,NULL,&gtree4);
                            SDL_DestroyTexture(imageTexture);

                            SDL_Rect gtree5 = {8 , SCREEN_HEIGHT / 22+400+120, 100,100};
                            SDL_RenderCopy(gRenderer,gtree1Tex,NULL,&gtree5);
                            SDL_DestroyTexture(imageTexture);


                            SDL_Rect gtree6 = {8 , SCREEN_HEIGHT / 22+400+150, 100,100};
                            SDL_RenderCopy(gRenderer,gtree1Tex,NULL,&gtree6);
                            SDL_DestroyTexture(imageTexture);


                            SDL_Rect gtree7 = {8+SCREEN_WIDTH /12+22 , SCREEN_HEIGHT / 22+400, 100,100};
                            SDL_RenderCopy(gRenderer,gtree1Tex,NULL,&gtree7);
                            SDL_DestroyTexture(imageTexture);


                            SDL_Rect gtree8 = {8+SCREEN_WIDTH /12+22 , SCREEN_HEIGHT / 22+400+30, 100,100};
                            // loadFromFile("tree-top.png");
                            SDL_RenderCopy(gRenderer,gtree1Tex,NULL,&gtree8);
                            SDL_DestroyTexture(imageTexture);


                            SDL_Rect gtree9 = {8+SCREEN_WIDTH /12+22 , SCREEN_HEIGHT / 22+400+60, 100,100};
                            // loadFromFile("tree-top.png");
                            SDL_RenderCopy(gRenderer,gtree1Tex,NULL,&gtree9);
                            SDL_DestroyTexture(imageTexture);

                            SDL_Rect gtree10 = {8+SCREEN_WIDTH /12+22 , SCREEN_HEIGHT / 22+400+90, 100,100};
                            // loadFromFile("tree-top.png");
                            SDL_RenderCopy(gRenderer,gtree1Tex,NULL,&gtree10);
                            SDL_DestroyTexture(imageTexture);

                            SDL_Rect gtree11 = {8+SCREEN_WIDTH /12+22 , SCREEN_HEIGHT / 22+400+120, 100,100};
                            // loadFromFile("tree-top.png");
                            SDL_RenderCopy(gRenderer,gtree1Tex,NULL,&gtree11);
                            SDL_DestroyTexture(imageTexture);


                            SDL_Rect gtree12 = {8+SCREEN_WIDTH /12+22 , SCREEN_HEIGHT / 22+400+150, 100,100};
                            // loadFromFile("tree-top.png");
                            SDL_RenderCopy(gRenderer,gtree1Tex,NULL,&gtree12);
                            SDL_DestroyTexture(imageTexture);
                            
                
                SDL_Rect gtree16 = {(int)(SCREEN_WIDTH*0.4)+45,(int)(SCREEN_HEIGHT*0.3)-60, 100,100};
                                            SDL_RenderCopy(gRenderer,gtree1Tex,NULL,&gtree16);
                                            SDL_Rect gtree17 = {(int)(SCREEN_WIDTH*0.4)+75,(int)(SCREEN_HEIGHT*0.3)-60, 100,100};
                                            SDL_RenderCopy(gRenderer,gtree1Tex,NULL,&gtree17);
                                            SDL_Rect gtree18 = {(int)(SCREEN_WIDTH*0.4)+105,(int)(SCREEN_HEIGHT*0.3)-60, 100,100};
                                            SDL_RenderCopy(gRenderer,gtree1Tex,NULL,&gtree18);
                                            SDL_Rect gtree19 = {(int)(SCREEN_WIDTH*0.4)+135,(int)(SCREEN_HEIGHT*0.3)-60, 100,100};
                                            SDL_RenderCopy(gRenderer,gtree1Tex,NULL,&gtree19);
                                            SDL_Rect gtree20 = {(int)(SCREEN_WIDTH*0.4)+165,(int)(SCREEN_HEIGHT*0.3)-60, 100,100};
                                            SDL_RenderCopy(gRenderer,gtree1Tex,NULL,&gtree20);
                                            SDL_Rect gtree21 = {(int)(SCREEN_WIDTH*0.4)+195,(int)(SCREEN_HEIGHT*0.3)-60, 100,100};
                                            SDL_RenderCopy(gRenderer,gtree1Tex,NULL,&gtree21);
                                            SDL_Rect gtree22 = {(int)(SCREEN_WIDTH*0.4)+225,(int)(SCREEN_HEIGHT*0.3)-60, 100,100};
                                            SDL_RenderCopy(gRenderer,gtree1Tex,NULL,&gtree22);
                                            SDL_Rect gtree23 = {(int)(SCREEN_WIDTH*0.4)+255,(int)(SCREEN_HEIGHT*0.3)-60, 100,100};
                                            SDL_RenderCopy(gRenderer,gtree1Tex,NULL,&gtree23);
                                            SDL_Rect gtree24 = {(int)(SCREEN_WIDTH*0.4)+285,(int)(SCREEN_HEIGHT*0.3)-60, 100,100};
                                            SDL_RenderCopy(gRenderer,gtree1Tex,NULL,&gtree24);

                                            // //////////////

                                            
                                            
                                            SDL_Rect gtree28 = {(int)(SCREEN_WIDTH*0.4)+45,(int)(SCREEN_HEIGHT*0.3)-90, 100,100};
                                            SDL_RenderCopy(gRenderer,gtree1Tex,NULL,&gtree28);
                                            SDL_Rect gtree29 = {(int)(SCREEN_WIDTH*0.4)+75,(int)(SCREEN_HEIGHT*0.3)-90, 100,100};
                                            SDL_RenderCopy(gRenderer,gtree1Tex,NULL,&gtree29);
                                            SDL_Rect gtree30 = {(int)(SCREEN_WIDTH*0.4)+105,(int)(SCREEN_HEIGHT*0.3)-90, 100,100};
                                            SDL_RenderCopy(gRenderer,gtree1Tex,NULL,&gtree30);
                                            SDL_Rect gtree31 = {(int)(SCREEN_WIDTH*0.4)+135,(int)(SCREEN_HEIGHT*0.3)-90, 100,100};
                                            SDL_RenderCopy(gRenderer,gtree1Tex,NULL,&gtree31);
                                            

                                            /////////////

                                            
                                         
                                            SDL_Rect gtree35 = {(int)(SCREEN_WIDTH*0.4)+45,(int)(SCREEN_HEIGHT*0.3)-120, 100,100};
                                            SDL_RenderCopy(gRenderer,gtree1Tex,NULL,&gtree35);
                                            SDL_Rect gtree36 = {(int)(SCREEN_WIDTH*0.4)+75,(int)(SCREEN_HEIGHT*0.3)-120, 100,100};
                                            SDL_RenderCopy(gRenderer,gtree1Tex,NULL,&gtree36);
                                            SDL_Rect gtree37 = {(int)(SCREEN_WIDTH*0.4)+105,(int)(SCREEN_HEIGHT*0.3)-120, 100,100};
                                            SDL_RenderCopy(gRenderer,gtree1Tex,NULL,&gtree37);
                                            SDL_Rect gtree38 = {(int)(SCREEN_WIDTH*0.4)+135,(int)(SCREEN_HEIGHT*0.3)-120, 100,100};
                                            SDL_RenderCopy(gRenderer,gtree1Tex,NULL,&gtree38);

                                            
                                            
                                            SDL_Rect gtree41 = {(int)(SCREEN_WIDTH*0.4)+45,(int)(SCREEN_HEIGHT*0.3)-150, 100,100};
                                            SDL_RenderCopy(gRenderer,gtree1Tex,NULL,&gtree41);
                                            SDL_Rect gtree42 = {(int)(SCREEN_WIDTH*0.4)+75,(int)(SCREEN_HEIGHT*0.3)-150, 100,100};
                                            SDL_RenderCopy(gRenderer,gtree1Tex,NULL,&gtree42);
                                            SDL_Rect gtree43 = {(int)(SCREEN_WIDTH*0.4)+105,(int)(SCREEN_HEIGHT*0.3)-150, 100,100};
                                            SDL_RenderCopy(gRenderer,gtree1Tex,NULL,&gtree43);
                                            SDL_Rect gtree44 = {(int)(SCREEN_WIDTH*0.4)+135,(int)(SCREEN_HEIGHT*0.3)-150, 100,100};
                                            SDL_RenderCopy(gRenderer,gtree1Tex,NULL,&gtree44);

                                            SDL_Rect gtree45 = {(int)(SCREEN_WIDTH*0.4)-200,(int)(SCREEN_HEIGHT*0.3)-150, 100,100};
                                            SDL_RenderCopy(gRenderer,gtree1Tex,NULL,&gtree45);
                                            SDL_Rect gtree46 = {(int)(SCREEN_WIDTH*0.4)-230,(int)(SCREEN_HEIGHT*0.3)-150, 100,100};
                                            SDL_RenderCopy(gRenderer,gtree1Tex,NULL,&gtree46);
                                            SDL_Rect gtree47 = {(int)(SCREEN_WIDTH*0.4)-260,(int)(SCREEN_HEIGHT*0.3)-150, 100,100};
                                            SDL_RenderCopy(gRenderer,gtree1Tex,NULL,&gtree47);
                                            SDL_Rect gtree48 = {(int)(SCREEN_WIDTH*0.4)-290,(int)(SCREEN_HEIGHT*0.3)-150, 100,100};
                                            SDL_RenderCopy(gRenderer,gtree1Tex,NULL,&gtree48);
                                            SDL_Rect gtree49 = {(int)(SCREEN_WIDTH*0.4)-320,(int)(SCREEN_HEIGHT*0.3)-150, 100,100};
                                            SDL_RenderCopy(gRenderer,gtree1Tex,NULL,&gtree49);
                                            SDL_Rect gtree50 = {(int)(SCREEN_WIDTH*0.4)-350,(int)(SCREEN_HEIGHT*0.3)-150, 100,100};
                                            SDL_RenderCopy(gRenderer,gtree1Tex,NULL,&gtree50);


                                            SDL_Rect gtree51 = {(int)(SCREEN_WIDTH*0.4)-200,(int)(SCREEN_HEIGHT*0.3)-120, 100,100};
                                            SDL_RenderCopy(gRenderer,gtree1Tex,NULL,&gtree51);
                                            SDL_Rect gtree52 = {(int)(SCREEN_WIDTH*0.4)-230,(int)(SCREEN_HEIGHT*0.3)-120, 100,100};
                                            SDL_RenderCopy(gRenderer,gtree1Tex,NULL,&gtree52);
                                            SDL_Rect gtree53 = {(int)(SCREEN_WIDTH*0.4)-260,(int)(SCREEN_HEIGHT*0.3)-120, 100,100};
                                            SDL_RenderCopy(gRenderer,gtree1Tex,NULL,&gtree53);
                                            SDL_Rect gtree54 = {(int)(SCREEN_WIDTH*0.4)-290,(int)(SCREEN_HEIGHT*0.3)-120, 100,100};
                                            SDL_RenderCopy(gRenderer,gtree1Tex,NULL,&gtree54);
                                            SDL_Rect gtree55 = {(int)(SCREEN_WIDTH*0.4)-320,(int)(SCREEN_HEIGHT*0.3)-120, 100,100};
                                            SDL_RenderCopy(gRenderer,gtree1Tex,NULL,&gtree55);
                                            SDL_Rect gtree56 = {(int)(SCREEN_WIDTH*0.4)-350,(int)(SCREEN_HEIGHT*0.3)-120, 100,100};
                                            SDL_RenderCopy(gRenderer,gtree1Tex,NULL,&gtree56);

                                            SDL_Rect gtree57 = {(int)(SCREEN_WIDTH*0.4)-450,(int)(SCREEN_HEIGHT*0.3)-120, 100,100};
                                            SDL_RenderCopy(gRenderer,gtree1Tex,NULL,&gtree57);
                                            SDL_Rect gtree58 = {(int)(SCREEN_WIDTH*0.4)-480,(int)(SCREEN_HEIGHT*0.3)-120, 100,100};
                                            SDL_RenderCopy(gRenderer,gtree1Tex,NULL,&gtree58);
                                            SDL_Rect gtree59 = {(int)(SCREEN_WIDTH*0.4)-510,(int)(SCREEN_HEIGHT*0.3)-120, 100,100};
                                            SDL_RenderCopy(gRenderer,gtree1Tex,NULL,&gtree59);
                                            SDL_Rect gtree60 = {(int)(SCREEN_WIDTH*0.4)-540,(int)(SCREEN_HEIGHT*0.3)-120, 100,100};
                                            SDL_RenderCopy(gRenderer,gtree1Tex,NULL,&gtree60);
                                            

                                            SDL_Rect gtree63 = {(int)(SCREEN_WIDTH*0.4)-450,(int)(SCREEN_HEIGHT*0.3)-150, 100,100};
                                            SDL_RenderCopy(gRenderer,gtree1Tex,NULL,&gtree63);
                                            SDL_Rect gtree64 = {(int)(SCREEN_WIDTH*0.4)-480,(int)(SCREEN_HEIGHT*0.3)-150, 100,100};
                                            SDL_RenderCopy(gRenderer,gtree1Tex,NULL,&gtree64);
                                            SDL_Rect gtree65 = {(int)(SCREEN_WIDTH*0.4)-510,(int)(SCREEN_HEIGHT*0.3)-150, 100,100};
                                            SDL_RenderCopy(gRenderer,gtree1Tex,NULL,&gtree65);
                                            SDL_Rect gtree66 = {(int)(SCREEN_WIDTH*0.4)-540,(int)(SCREEN_HEIGHT*0.3)-150, 100,100};
                                            SDL_RenderCopy(gRenderer,gtree1Tex,NULL,&gtree66);
                                            

                                            SDL_Rect gtree69 = {(int)(SCREEN_WIDTH*0.4)-450,(int)(SCREEN_HEIGHT*0.3)-90, 100,100};
                                            SDL_RenderCopy(gRenderer,gtree1Tex,NULL,&gtree69);
                                            SDL_Rect gtree70 = {(int)(SCREEN_WIDTH*0.4)-480,(int)(SCREEN_HEIGHT*0.3)-90, 100,100};
                                            SDL_RenderCopy(gRenderer,gtree1Tex,NULL,&gtree70);
                                            SDL_Rect gtree71 = {(int)(SCREEN_WIDTH*0.4)-510,(int)(SCREEN_HEIGHT*0.3)-90, 100,100};
                                            SDL_RenderCopy(gRenderer,gtree1Tex,NULL,&gtree71);
                                            SDL_Rect gtree72 = {(int)(SCREEN_WIDTH*0.4)-540,(int)(SCREEN_HEIGHT*0.3)-90, 100,100};
                                            SDL_RenderCopy(gRenderer,gtree1Tex,NULL,&gtree72);
                                            


                                            SDL_Rect peacock1 = {(int)(SCREEN_WIDTH*0.4)-600,(int)(SCREEN_HEIGHT*0.3)-100, 80,80};
                                            if((tempClip/10)%9==0){
                                                SDL_RenderCopy(gRenderer,peacockframeTex1,NULL,&peacock1);
                                            }
                                            else if((tempClip/10)%9==1){
                                                SDL_RenderCopy(gRenderer,peacockframeTex2,NULL,&peacock1);
                                            }
                                            else if((tempClip/10)%9==2){
                                                SDL_RenderCopy(gRenderer,peacockframeTex3,NULL,&peacock1);
                                            }
                                            else if((tempClip/10)%9==3){
                                                SDL_RenderCopy(gRenderer,peacockframeTex4,NULL,&peacock1);
                                            }
                                            else if((tempClip/10)%9==4){
                                                SDL_RenderCopy(gRenderer,peacockframeTex5,NULL,&peacock1);
                                            }
                                            else if((tempClip/10)%9==5){
                                                SDL_RenderCopy(gRenderer,peacockframeTex4,NULL,&peacock1);
                                            }
                                            else if((tempClip/10)%9==6){
                                                SDL_RenderCopy(gRenderer,peacockframeTex3,NULL,&peacock1);
                                            }
                                            else if((tempClip/10)%9==7){
                                                SDL_RenderCopy(gRenderer,peacockframeTex2,NULL,&peacock1);
                                            }
                                            else if((tempClip/10)%9==8){
                                                SDL_RenderCopy(gRenderer,peacockframeTex1,NULL,&peacock1);
                                            }


                                            SDL_Rect peacock2 = {(int)(SCREEN_WIDTH*0.4)+500,(int)(SCREEN_HEIGHT*0.3)-100, 80,80};
                                            if((tempClip/10)%9==0){
                                                SDL_RenderCopy(gRenderer,peacockframeTex1,NULL,&peacock2);
                                            }
                                            else if((tempClip/10)%9==1){
                                                SDL_RenderCopy(gRenderer,peacockframeTex2,NULL,&peacock2);
                                            }
                                            else if((tempClip/10)%9==2){
                                                SDL_RenderCopy(gRenderer,peacockframeTex3,NULL,&peacock2);
                                            }
                                            else if((tempClip/10)%9==3){
                                                SDL_RenderCopy(gRenderer,peacockframeTex4,NULL,&peacock2);
                                            }
                                            else if((tempClip/10)%9==4){
                                                SDL_RenderCopy(gRenderer,peacockframeTex5,NULL,&peacock2);
                                            }
                                            else if((tempClip/10)%9==5){
                                                SDL_RenderCopy(gRenderer,peacockframeTex4,NULL,&peacock2);
                                            }
                                            else if((tempClip/10)%9==6){
                                                SDL_RenderCopy(gRenderer,peacockframeTex3,NULL,&peacock2);
                                            }
                                            else if((tempClip/10)%9==7){
                                                SDL_RenderCopy(gRenderer,peacockframeTex2,NULL,&peacock2);
                                            }
                                            else if((tempClip/10)%9==8){
                                                SDL_RenderCopy(gRenderer,peacockframeTex1,NULL,&peacock2);
                                            }

                                            SDL_Rect peacock3 = {(int)(SCREEN_WIDTH*0.4)+10,(int)(SCREEN_HEIGHT*0.3)-100, 80,80};
                                            if((tempClip/10)%9==0){
                                                SDL_RenderCopy(gRenderer,peacockframeTex1,NULL,&peacock3);
                                            }
                                            else if((tempClip/10)%9==1){
                                                SDL_RenderCopy(gRenderer,peacockframeTex2,NULL,&peacock3);
                                            }
                                            else if((tempClip/10)%9==2){
                                                SDL_RenderCopy(gRenderer,peacockframeTex3,NULL,&peacock3);
                                            }
                                            else if((tempClip/10)%9==3){
                                                SDL_RenderCopy(gRenderer,peacockframeTex4,NULL,&peacock3);
                                            }
                                            else if((tempClip/10)%9==4){
                                                SDL_RenderCopy(gRenderer,peacockframeTex5,NULL,&peacock3);
                                            }
                                            else if((tempClip/10)%9==5){
                                                SDL_RenderCopy(gRenderer,peacockframeTex4,NULL,&peacock3);
                                            }
                                            else if((tempClip/10)%9==6){
                                                SDL_RenderCopy(gRenderer,peacockframeTex3,NULL,&peacock3);
                                            }
                                            else if((tempClip/10)%9==7){
                                                SDL_RenderCopy(gRenderer,peacockframeTex2,NULL,&peacock3);
                                            }
                                            else if((tempClip/10)%9==8){
                                                SDL_RenderCopy(gRenderer,peacockframeTex1,NULL,&peacock3);
                                            }

                                            SDL_Rect peacock4 = {(int)(SCREEN_WIDTH*0.4)+86,(int)(SCREEN_HEIGHT*0.3)+110, 70,70};
                                            if((tempClip/10)%9==0){
                                                SDL_RenderCopy(gRenderer,peacockframeTex1,NULL,&peacock4);
                                            }
                                            else if((tempClip/10)%9==1){
                                                SDL_RenderCopy(gRenderer,peacockframeTex2,NULL,&peacock4);
                                            }
                                            else if((tempClip/10)%9==2){
                                                SDL_RenderCopy(gRenderer,peacockframeTex3,NULL,&peacock4);
                                            }
                                            else if((tempClip/10)%9==3){
                                                SDL_RenderCopy(gRenderer,peacockframeTex4,NULL,&peacock4);
                                            }
                                            else if((tempClip/10)%9==4){
                                                SDL_RenderCopy(gRenderer,peacockframeTex5,NULL,&peacock4);
                                            }
                                            else if((tempClip/10)%9==5){
                                                SDL_RenderCopy(gRenderer,peacockframeTex4,NULL,&peacock4);
                                            }
                                            else if((tempClip/10)%9==6){
                                                SDL_RenderCopy(gRenderer,peacockframeTex3,NULL,&peacock4);
                                            }
                                            else if((tempClip/10)%9==7){
                                                SDL_RenderCopy(gRenderer,peacockframeTex2,NULL,&peacock4);
                                            }
                                            else if((tempClip/10)%9==8){
                                                SDL_RenderCopy(gRenderer,peacockframeTex1,NULL,&peacock4);
                                            }
                                            tempClip++;

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
                            SDL_Rect dog = {prd.first,prd.second,80,80};
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

                            SDL_Rect jetTop = {1220,104,300,300};
                            if(player1.purchasedJetPack){
                                    SDL_RenderCopy(gRenderer,jetTopTex,NULL,&jetTop);
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
                                                                case SDLK_j:
                                                                        player1.changeJetPack();
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
                    SDL_Rect ttable = {  (int)(0.2*SCREEN_WIDTH) , (int)(0.6*SCREEN_HEIGHT), 250, 250 };
                    SDL_RenderCopy(gRenderer,ttableTex,NULL,&ttable);

                    // loading messarea
                    SDL_Rect mess = {  (int)(0.5*SCREEN_WIDTH) , (int)(0.5*SCREEN_HEIGHT), 400, 400 };
                    SDL_RenderCopy(gRenderer,messTex,NULL,&mess);

                
               
                //     load cat1
                    SDL_Rect cat1 = {  300 , 400, 100, 100 };
                    
                    if((temp11Clip/20)%5==0){
                        SDL_RenderCopy(gRenderer,catTex1,NULL,&cat1);
                    }
                    else if((temp11Clip/20)%5==1){
                        SDL_RenderCopy(gRenderer,catTex2,NULL,&cat1);
                    }
                    else if((temp11Clip/20)%5==2){
                        SDL_RenderCopy(gRenderer,catTex3,NULL,&cat1);
                    }
                    else if((temp11Clip/20)%5==3){
                        SDL_RenderCopy(gRenderer,catTex2,NULL,&cat1);
                    }
                    else if((temp11Clip/20)%5==4){
                        SDL_RenderCopy(gRenderer,catTex1,NULL,&cat1);
                    }
                    
                    

                    // load cat2
                    SDL_Rect cat2 = {  300+800 , 400+400, 100, 100 };
                    if((temp11Clip/20)%5==0){
                        SDL_RenderCopy(gRenderer,catTex1,NULL,&cat2);
                    }
                    else if((temp11Clip/20)%5==1){
                        SDL_RenderCopy(gRenderer,catTex2,NULL,&cat2);
                    }
                    else if((temp11Clip/20)%5==2){
                        SDL_RenderCopy(gRenderer,catTex3,NULL,&cat2);
                    }
                    else if((temp11Clip/20)%5==3){
                        SDL_RenderCopy(gRenderer,catTex2,NULL,&cat2);
                    }
                    else if((temp11Clip/20)%5==4){
                        SDL_RenderCopy(gRenderer,catTex1,NULL,&cat2);
                    }



                    // load cat3
                    SDL_Rect cat3 = {  500 , 500, 100, 100 };
                    if((temp11Clip/20)%5==0){
                        SDL_RenderCopy(gRenderer,catTex1,NULL,&cat3);
                    }
                    else if((temp11Clip/20)%5==1){
                        SDL_RenderCopy(gRenderer,catTex2,NULL,&cat3);
                    }
                    else if((temp11Clip/20)%5==2){
                        SDL_RenderCopy(gRenderer,catTex3,NULL,&cat3);
                    }
                    else if((temp11Clip/20)%5==3){
                        SDL_RenderCopy(gRenderer,catTex2,NULL,&cat3);
                    }
                    else if((temp11Clip/20)%5==4){
                        SDL_RenderCopy(gRenderer,catTex1,NULL,&cat3);
                    }


                    // load cat4
                    SDL_Rect cat4 = {  550 , 750, 100, 100 };
                    if((temp11Clip/20)%5==0){
                        SDL_RenderCopy(gRenderer,catTex1,NULL,&cat4);
                    }
                    else if((temp11Clip/20)%5==1){
                        SDL_RenderCopy(gRenderer,catTex2,NULL,&cat4);
                    }
                    else if((temp11Clip/20)%5==2){
                        SDL_RenderCopy(gRenderer,catTex3,NULL,&cat4);
                    }
                    else if((temp11Clip/20)%5==3){
                        SDL_RenderCopy(gRenderer,catTex2,NULL,&cat4);
                    }
                    else if((temp11Clip/20)%5==4){
                        SDL_RenderCopy(gRenderer,catTex1,NULL,&cat4);
                    }




                    // load rabbit5
                    SDL_Rect cat5 = {  350 , 850, 100, 100 };
                    if((temp11Clip/20)%5==0){
                        SDL_RenderCopy(gRenderer,catTex1,NULL,&cat5);
                    }
                    else if((temp11Clip/20)%5==1){
                        SDL_RenderCopy(gRenderer,catTex2,NULL,&cat5);
                    }
                    else if((temp11Clip/20)%5==2){
                        SDL_RenderCopy(gRenderer,catTex3,NULL,&cat5);
                    }
                    else if((temp11Clip/20)%5==3){
                        SDL_RenderCopy(gRenderer,catTex2,NULL,&cat5);
                    }
                    else if((temp11Clip/20)%5==4){
                        SDL_RenderCopy(gRenderer,catTex1,NULL,&cat5);
                    }



                    // load rabbit6
                    SDL_Rect cat6 = {  650 , 750, 100, 100 };
                    if((temp11Clip/20)%5==0){
                        SDL_RenderCopy(gRenderer,catTex1,NULL,&cat6);
                    }
                    else if((temp11Clip/20)%5==1){
                        SDL_RenderCopy(gRenderer,catTex2,NULL,&cat6);
                    }
                    else if((temp11Clip/20)%5==2){
                        SDL_RenderCopy(gRenderer,catTex3,NULL,&cat6);
                    }
                    else if((temp11Clip/20)%5==3){
                        SDL_RenderCopy(gRenderer,catTex2,NULL,&cat6);
                    }
                    else if((temp11Clip/20)%5==4){
                        SDL_RenderCopy(gRenderer,catTex1,NULL,&cat6);
                    }




                //     // load rabbit7
                //     SDL_Rect cat7 = {  850 , 650, 100, 100 };
                //     if((temp11Clip/20)%5==0){
                //         SDL_RenderCopy(gRenderer,catTex1,NULL,&cat7);
                //     }
                //     else if((temp11Clip/20)%5==1){
                //         SDL_RenderCopy(gRenderer,catTex2,NULL,&cat7);
                //     }
                //     else if((temp11Clip/20)%5==2){
                //         SDL_RenderCopy(gRenderer,catTex3,NULL,&cat7);
                //     }
                //     else if((temp11Clip/20)%5==3){
                //         SDL_RenderCopy(gRenderer,catTex2,NULL,&cat7);
                //     }
                //     else if((temp11Clip/20)%5==4){
                //         SDL_RenderCopy(gRenderer,catTex1,NULL,&cat7);
                //     }
                    temp11Clip+=1;


                    // load room
                    SDL_Rect room = {  (int)(0.6*SCREEN_WIDTH) , 0, 300, 300 };

                    SDL_RenderCopy(gRenderer,roomTex,NULL,&room);


                    /*
                    // rendering trees
                    
                    SDL_Rect tree_top = {  1140 , 850, 200, 200 };
                    SDL_RenderCopy(gRenderer,tree_topTex,NULL,&tree_top);
                    tree_top = {  160 , 850, 200, 200 };
                    SDL_RenderCopy(gRenderer,tree_topTex,NULL,&tree_top);
                    tree_top = {  1140 , 280, 200, 200 };
                    SDL_RenderCopy(gRenderer,tree_rightTex,NULL,&tree_top);
                    tree_top = {  230 , 250, 200, 200 };
                    SDL_RenderCopy(gRenderer,tree_leftTex,NULL,&tree_top);
                    */

                    // entry exit

                    SDL_Rect entry_exit = {  0 , (int)(0.3*SCREEN_HEIGHT), 300, 300 };

                    SDL_RenderCopy(gRenderer,entry_exitTex,NULL,&entry_exit);

                    // caretaker office

                    SDL_Rect caretaker = {  (int)(0.2*SCREEN_WIDTH) , 0, 300, 300 };

                    SDL_RenderCopy(gRenderer,caretakerTex,NULL,&caretaker);

                    // washroom

                    //SDL_Rect washroom = { 1180 , 600, 200, 200 };

//                    SDL_RenderCopy(gRenderer,washroomTex,NULL,&washroom);

                    SDL_SetRenderDrawColor( gRenderer,235, 52, 155, 0xFF );
                    SDL_Rect workers = {50,800,250/3,250};
                    SDL_RenderCopy(gRenderer,workerSprites,&arr[(tempClip/10)%3],&workers);
                    //SDL_Rect workers2 = {50,300,250/3,250};
                    //SDL_RenderCopy(gRenderer,workerSprites,&arr[(tempClip/20)%3],&workers2);

                    if(temp2Clip <90){
                            if((temp2Clip/10)%9==0){
                                SDL_RenderCopy(gRenderer,ttframe2Tex,NULL,&ttable);
                            }
                            else if((temp2Clip/10)%9==1){
                                SDL_RenderCopy(gRenderer,ttframe3Tex,NULL,&ttable);
                            }
                            else if((temp2Clip/10)%9==2){
                                SDL_RenderCopy(gRenderer,ttframe4Tex,NULL,&ttable);
                            }
                            else if((temp2Clip/10)%9==3){
                                SDL_RenderCopy(gRenderer,ttframe5Tex,NULL,&ttable);
                            }
                            else if((temp2Clip/10)%9==4){
                                SDL_RenderCopy(gRenderer,ttframe6Tex,NULL,&ttable);
                            }
                            else if((temp2Clip/10)%9==5){
                                SDL_RenderCopy(gRenderer,ttframe7Tex,NULL,&ttable);
                            }
                            else if((temp2Clip/10)%9==6){
                                SDL_RenderCopy(gRenderer,ttframe8Tex,NULL,&ttable);
                            }
                            else if((temp2Clip/10)%9==7){
                                SDL_RenderCopy(gRenderer,ttframe9Tex,NULL,&ttable);
                            }
                            else if((temp2Clip/10)%9==8){
                                SDL_RenderCopy(gRenderer,ttframe10Tex,NULL,&ttable);
                            }
                            
                    }

                    if(temp3Clip <40){
                            if((temp3Clip/10)%4==0){
                                SDL_RenderCopy(gRenderer,messframe1Tex,NULL,&mess);
                            }
                            else if((temp3Clip/10)%4==1){
                                SDL_RenderCopy(gRenderer,messframe2Tex,NULL,&mess);
                            }
                            else if((temp3Clip/10)%4==2){
                                SDL_RenderCopy(gRenderer,messframe3Tex,NULL,&mess);
                            }
                            else if((temp3Clip/10)%4==3){
                                SDL_RenderCopy(gRenderer,messframe4Tex,NULL,&mess);
                            }
                    }

                    temp3Clip+=1;
                    temp2Clip+=1;
                    tempClip = tempClip+1;
                    player1.renderPlayer();
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

                        if(temp6Clip <60){
                            if((temp6Clip/10)%6==0){
                                SDL_RenderCopy(gRenderer,footballframe1Tex,NULL,&largeGroundInner);
                            }
                            else if((temp6Clip/10)%6==1){
                                SDL_RenderCopy(gRenderer,footballframe2Tex,NULL,&largeGroundInner);
                            }
                            else if((temp6Clip/10)%6==2){
                                SDL_RenderCopy(gRenderer,footballframe3Tex,NULL,&largeGroundInner);
                            }
                            else if((temp6Clip/10)%6==3){
                                SDL_RenderCopy(gRenderer,footballframe4Tex,NULL,&largeGroundInner);
                            }
                            else if((temp6Clip/10)%6==4){
                                SDL_RenderCopy(gRenderer,footballframe5Tex,NULL,&largeGroundInner);
                            }
                            else if((temp6Clip/10)%6==5){
                                SDL_RenderCopy(gRenderer,footballframe6Tex,NULL,&largeGroundInner);
                            }
                        }
                        temp6Clip+=1;

                        if(temp7Clip <60){
                            if((temp7Clip/10)%6==0){
                                SDL_RenderCopy(gRenderer,cricketframe1Tex,NULL,&largeGroundInner);
                            }
                            else if((temp7Clip/10)%6==1){
                                SDL_RenderCopy(gRenderer,cricketframe2Tex,NULL,&largeGroundInner);
                            }
                            else if((temp7Clip/10)%6==2){
                                SDL_RenderCopy(gRenderer,cricketframe3Tex,NULL,&largeGroundInner);
                            }
                            else if((temp7Clip/10)%6==3){
                                SDL_RenderCopy(gRenderer,cricketframe4Tex,NULL,&largeGroundInner);
                            }
                            else if((temp7Clip/10)%6==4){
                                SDL_RenderCopy(gRenderer,cricketframe5Tex,NULL,&largeGroundInner);
                            }
                            else if((temp7Clip/10)%6==5){
                                SDL_RenderCopy(gRenderer,cricketframe6Tex,NULL,&largeGroundInner);
                            }
                        }
                        temp7Clip+=1;


                        if(temp8Clip <90){
                            if((temp8Clip/10)%9==0){
                                SDL_RenderCopy(gRenderer,hockeyframe1Tex,NULL,&largeGroundInner);
                            }
                            else if((temp8Clip/10)%9==1){
                                SDL_RenderCopy(gRenderer,hockeyframe2Tex,NULL,&largeGroundInner);
                            }
                            else if((temp8Clip/10)%9==2){
                                SDL_RenderCopy(gRenderer,hockeyframe3Tex,NULL,&largeGroundInner);
                            }
                            else if((temp8Clip/10)%9==3){
                                SDL_RenderCopy(gRenderer,hockeyframe4Tex,NULL,&largeGroundInner);
                            }
                            else if((temp8Clip/10)%9==4){
                                SDL_RenderCopy(gRenderer,hockeyframe5Tex,NULL,&largeGroundInner);
                            }
                            else if((temp8Clip/10)%9==5){
                                SDL_RenderCopy(gRenderer,hockeyframe6Tex,NULL,&largeGroundInner);
                            }
                            else if((temp8Clip/10)%9==6){
                                SDL_RenderCopy(gRenderer,hockeyframe7Tex,NULL,&largeGroundInner);
                            }
                            else if((temp8Clip/10)%9==7){
                                SDL_RenderCopy(gRenderer,hockeyframe8Tex,NULL,&largeGroundInner);
                            }
                            else if((temp8Clip/10)%9==8){
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

                        if(temp4Clip <60){
                            if((temp4Clip/10)%6==0){
                                SDL_RenderCopy(gRenderer,tennisframe1Tex,NULL,&tennisCourtInner);
                            }
                            else if((temp4Clip/10)%6==1){
                                SDL_RenderCopy(gRenderer,tennisframe2Tex,NULL,&tennisCourtInner);
                            }
                            else if((temp4Clip/10)%6==2){
                                SDL_RenderCopy(gRenderer,tennisframe3Tex,NULL,&tennisCourtInner);
                            }
                            else if((temp4Clip/10)%6==3){
                                SDL_RenderCopy(gRenderer,tennisframe4Tex,NULL,&tennisCourtInner);
                            }
                            else if((temp4Clip/10)%6==4){
                                SDL_RenderCopy(gRenderer,tennisframe5Tex,NULL,&tennisCourtInner);
                            }
                            else if((temp4Clip/10)%6==5){
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
                        if(temp5Clip<60){
                                if((temp5Clip/10)%6==0){
                                    SDL_RenderCopy(gRenderer,volleyballframeTex1,NULL,&volleyCourtInner);
                                }
                                else if((temp5Clip/10)%6==1){
                                    SDL_RenderCopy(gRenderer,volleyballframeTex2,NULL,&volleyCourtInner);
                                }
                                else if((temp5Clip/10)%6==2){
                                    SDL_RenderCopy(gRenderer,volleyballframeTex3,NULL,&volleyCourtInner);
                                }
                                else if((temp5Clip/10)%6==3){
                                    SDL_RenderCopy(gRenderer,volleyballframeTex4,NULL,&volleyCourtInner);
                                }
                                else if((temp5Clip/10)%6==4){
                                    SDL_RenderCopy(gRenderer,volleyballframeTex5,NULL,&volleyCourtInner);
                                }
                                else if((temp5Clip/10)%6==5){
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
                                    player1.happiness = max(player1.happiness-1, 0) ;
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
                                    player1.happiness = max(player1.happiness-1, 0) ;
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
                                    player1.happiness = max(player1.happiness-1, 0) ;
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
                    
                    if(temp12Clip<50){
                        if((temp12Clip/10)%5==0){
                            SDL_RenderCopy(gRenderer, pizzaframeTex1, NULL, &tile);
                        }
                        else if((temp12Clip/10)%5==1){
                            SDL_RenderCopy(gRenderer, pizzaframeTex2, NULL, &tile);
                        }
                        else if((temp12Clip/10)%5==2){
                            SDL_RenderCopy(gRenderer, pizzaframeTex3, NULL, &tile);
                        }
                        else if((temp12Clip/10)%5==3){
                            SDL_RenderCopy(gRenderer, pizzaframeTex4, NULL, &tile);
                        }
                        else if((temp12Clip/10)%5==4){
                            SDL_RenderCopy(gRenderer, restaurantTex, NULL, &tile);
                        }
                    }
                    temp12Clip+=1;
                    SDL_SetRenderDrawColor( gRenderer,235, 52, 155, 0xFF );
                    player1.renderPlayer();
                    if(player2.enterRestaurant && ((player1.enterMasalaMix && player2.enterMasalaMix) || (player1.enterCCD && player2.enterCCD) || (player1.enterAmul && player2.enterAmul) || (player1.enterShiru && player2.enterShiru) || (player1.enterNescafe && player2.enterNescafe) || (player1.enterChaayos && player2.enterChaayos) || (player1.enterRajdhani && player2.enterRajdhani) || (player1.enterStaffCanteen && player2.enterStaffCanteen) || (player1.enterDilli16 && player2.enterDilli16))){
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
                else if(player1.inOAT){
                    SDL_Rect danceOAT = {0,0,SCREEN_WIDTH,SCREEN_HEIGHT};
                                            if((tempClip/10)%5==0){
                                                    SDL_RenderCopy(gRenderer,oatinsideTex1,NULL,&danceOAT);
                                            }
                                            else if((tempClip/10)%5==1){
                                                    SDL_RenderCopy(gRenderer,oatinsideTex2,NULL,&danceOAT);
                                            }
                                            else if((tempClip/10)%5==2){
                                                    SDL_RenderCopy(gRenderer,oatinsideTex3,NULL,&danceOAT);
                                            }
                                            else if((tempClip/10)%5==3){
                                                    SDL_RenderCopy(gRenderer,oatinsideTex2,NULL,&danceOAT);
                                            }
                                            else if((tempClip/10)%5==4){
                                                    SDL_RenderCopy(gRenderer,oatinsideTex1,NULL,&danceOAT);
                                            }
                                            if(delay()){
                                                    player1.happiness = min(100,player1.happiness+1);
                                            }
                                            tempClip++;
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
                        player1.happiness = max(player1.happiness-1, 0) ;
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
                else if(player1.inCSC){
                        SDL_Rect computerScreen = {0,0,SCREEN_HEIGHT,SCREEN_HEIGHT};
                        SDL_RenderCopy(gRenderer,cscInsideTex,NULL,&computerScreen);
                        if(delay()){

                                        player1.energy = max(player1.energy-1,0);
                                        player1.health = max(player1.health-1,0);
                                        player1.knowledge = min(player1.knowledge+1,100);
                                        if(player1.health<=0 || player1.energy<=0){
                                                player1.hospitalize();
                                        }
                        player1.happiness = max(player1.happiness-1, 0) ;
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
                
                
                    

                    SDL_Rect happyface = {SCREEN_WIDTH-138,740,100,80};
                            SDL_Rect moneyRect = {SCREEN_WIDTH-120,700,60,60};
                            SDL_Rect knowledgeRect = {SCREEN_WIDTH-118,660,60,60};
                            SDL_Rect energyRect = {SCREEN_WIDTH-124,600,70,70};
                            SDL_Rect healthRect = {SCREEN_WIDTH-118,790,80,75};
                            string s= to_string(player1.happiness);
                            int n = s.length();
                            char char_array1[n + 1];
                            strcpy(char_array1, s.c_str());
                            if(player1.isReady && player2.isReady && !player1.won && !player1.lost){
                                if(player1.happiness<=100 && player1.happiness>80){
                                                                  happinessiconTex = happinessicon1Tex ;
                                                              }
                                                              else if(player1.happiness<=80 && player1.happiness>60){
                                                                  happinessiconTex = happinessicon2Tex ;
                                                              }
                                                              else if(player1.happiness<=60 && player1.happiness>40){
                                                                  happinessiconTex = happinessicon3Tex ;
                                                              }
                                                              else if(player1.happiness<=40 && player1.happiness>20){
                                                                  happinessiconTex = happinessicon4Tex ;
                                                              }
                                                              else if(player1.happiness<=20 && player1.happiness>0){
                                                                  happinessiconTex = happinessicon5Tex ;
                                                              }
                                                              
                                                              
                                                              
                                
                                
                                    SDL_RenderCopy(gRenderer,happinessiconTex,NULL,&happyface);
                                    disptext(gRenderer,  SCREEN_WIDTH-55,750,50,50, char_array1,146, 255, 138) ;
                            }
                            

                            s= to_string(player1.money);
                            n = s.length();
                            char char_array2[n + 1];
                            strcpy(char_array2, s.c_str());
                            if(player1.isReady && player2.isReady && !player1.won && !player1.lost){
                                    SDL_RenderCopy(gRenderer,moneyiconTex,NULL,&moneyRect);
                                    disptext(gRenderer,  SCREEN_WIDTH-55,700,50,50, char_array2,146, 255, 138) ;
                            }

                            s= to_string(player1.knowledge);
                            n = s.length();
                            char char_array3[n + 1];
                            strcpy(char_array3, s.c_str());
                            if(player1.isReady && player2.isReady&& !player1.won && !player1.lost){
                                    SDL_RenderCopy(gRenderer,bookiconTex,NULL,&knowledgeRect);
                                    disptext(gRenderer,  SCREEN_WIDTH-55,650,50,50, char_array3,146, 255, 138) ;
                            }

                            s= to_string(player1.energy);
                            n = s.length();
                            char char_array4[n + 1];
                            strcpy(char_array4, s.c_str());
                            if(player1.isReady && player2.isReady&& !player1.won && !player1.lost){
                                    
                                if(player1.energy<=100 && player1.energy>80){
                                                                  energyiconTex = energyicon1Tex ;
                                                              }
                                                              else if(player1.energy<=80 && player1.energy>60){
                                                                  energyiconTex = energyicon2Tex ;
                                                              }
                                                              else if(player1.energy<=60 && player1.energy>40){
                                                                  energyiconTex = energyicon3Tex ;
                                                              }
                                                              else if(player1.energy<=40 && player1.energy>20){
                                                                  energyiconTex = energyicon4Tex ;
                                                              }
                                                              else if(player1.energy<=20 && player1.energy>0){
                                                                  energyiconTex = energyicon5Tex ;
                                                              }
                                                              
                                
                                
                                    SDL_RenderCopy(gRenderer,energyiconTex,NULL,&energyRect);
                                    disptext(gRenderer,  SCREEN_WIDTH-55,600,50,50, char_array4,146, 255, 138) ;
                            }

                            s= to_string(player1.health);
                            n = s.length();
                            char char_array5[n + 1];
                            strcpy(char_array5, s.c_str());
                           if(player1.isReady && player2.isReady&& !player1.won && !player1.lost){
                               if(player1.health<=100 && player1.health>80){
                                   hearticonTex = hearticon1Tex ;
                               }
                               else if(player1.health<=80 && player1.health>60){
                                   hearticonTex = hearticon2Tex ;
                               }
                               else if(player1.health<=60 && player1.health>40){
                                   hearticonTex = hearticon3Tex ;
                               }
                               else if(player1.health<=40 && player1.health>20){
                                   hearticonTex = hearticon4Tex ;
                               }
                               else if(player1.health<=20 && player1.health>0){
                                   hearticonTex = hearticon5Tex ;
                               }
                               
                               
                                SDL_RenderCopy(gRenderer,hearticonTex,NULL,&healthRect);
                                    disptext(gRenderer,  SCREEN_WIDTH-55,800,50,50, char_array5,146, 255, 138) ;
                            }














                SDL_RenderPresent(gRenderer);

                }
        }








        

        



        return 0;
                
}
