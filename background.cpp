#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <string>
#include <vector>
using namespace std;
const int HOSPITAL_BILL = 90;

const int PLAYER_RADIUS = 10;
SDL_Window* gWindow = NULL;

//The window renderer
SDL_Renderer* gRenderer = NULL;

//Current displayed texture
SDL_Texture* gTexture = NULL;
enum KeyPress
{
    KEY_PRESS_UP,
    KEY_PRESS_DOWN,
    KEY_PRESS_LEFT,
    KEY_PRESS_RIGHT,
};

SDL_Texture* imageTexture = NULL;

bool loadFromFile( std::string path )
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

        return imageTexture != NULL;
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


void DrawCircle(SDL_Renderer * renderer, int32_t centreX, int32_t centreY, int32_t radius)
{
   const int32_t diameter = (radius * 2);

   int32_t x = (radius - 1);
   int32_t y = 0;
   int32_t tx = 1;
   int32_t ty = 1;
   int32_t error = (tx - diameter);

   while (x >= y)
   {
      //  Each of the following renders an octant of the circle
      SDL_RenderDrawPoint(renderer, centreX + x, centreY - y);
      SDL_RenderDrawPoint(renderer, centreX + x, centreY + y);
      SDL_RenderDrawPoint(renderer, centreX - x, centreY - y);
      SDL_RenderDrawPoint(renderer, centreX - x, centreY + y);
      SDL_RenderDrawPoint(renderer, centreX + y, centreY - x);
      SDL_RenderDrawPoint(renderer, centreX + y, centreY + x);
      SDL_RenderDrawPoint(renderer, centreX - y, centreY - x);
      SDL_RenderDrawPoint(renderer, centreX - y, centreY + x);

      if (error <= 0)
      {
         ++y;
         error += ty;
         ty += 2;
      }

      if (error > 0)
      {
         --x;
         tx += 2;
         error += (tx - diameter);
      }
   }
}

class Player{

        public:
                int x;
                int y;
                int speed = 2;
                int health;
                int energy;
                int happiness;
                int money;
                int knowledge;
                bool hasCycle;
                string color;
        Player(int xP,int yP,string colorP){
                health = 50;
                energy = 100;
                happiness = 50;
                money = 100;
                knowledge = 10;
                hasCycle = false;
                x = xP;
                y = yP;
                color = colorP;
        }


        void buyCycleIfPossible(){
                if(money>200 && !hasCycle){
                        money-=200;
                        energy*=2;
                        hasCycle = true;

                }
                
        }

        void hospitalize(){
                money-=HOSPITAL_BILL;
                energy = 100;
                health = 100;
                happiness = 50;
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
                speed = 2+energy/10;
        }

        void move(int keyPress){
                if(keyPress == KEY_PRESS_UP){
                        y-=speed;
                }
                if(keyPress == KEY_PRESS_DOWN){
                        y+=speed;
                }
                if(keyPress == KEY_PRESS_LEFT){
                        x-=speed;
                }
                if(keyPress == KEY_PRESS_RIGHT){
                        x+=speed;
                }
        }

        void renderPlayer(){
                SDL_Rect player1 = {x,y,30,30};
                loadFromFile(color+"-char.png");
                SDL_RenderCopy(gRenderer,imageTexture,NULL,&player1);
                SDL_DestroyTexture(imageTexture);
        }

};

const int SCREEN_WIDTH = 1520;
const int SCREEN_HEIGHT = 1020;

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
                gWindow = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
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

        //Destroy window        
        SDL_DestroyRenderer( gRenderer );
        SDL_DestroyWindow( gWindow );
        gWindow = NULL;
        gRenderer = NULL;
        imageTexture = NULL;
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
                SDL_Rect textRect = {SCREEN_WIDTH-160,800,140,50};
                // gFont = TTF_OpenFont( "Pacifico.ttf", 1000 );

                Player player1 = Player(0,0,"pink");
                Player player2 = Player(SCREEN_WIDTH-20,20,"purple");
		bool quit = false;

		SDL_Event e;

		while(!quit){

			

			SDL_SetRenderDrawColor(gRenderer,0x00,0x00,0x00,0x00);
			SDL_RenderClear(gRenderer);
			
			// Nilgiri
	    SDL_Rect nilgiri = { SCREEN_WIDTH / 22, SCREEN_HEIGHT / 22, SCREEN_WIDTH / 10, SCREEN_HEIGHT / 10 };
            loadFromFile("nilgiri.png");

            // SDL_SetTextInputRect(&fillRect);
       
            SDL_RenderCopy(gRenderer,imageTexture,NULL,&nilgiri);
            SDL_DestroyTexture(imageTexture);
			// SDL_RenderCopy(gRenderer,gTexture, NULL, NULL);

           
//writing text in the box

            // disptext(gRenderer, SCREEN_WIDTH / 22, SCREEN_HEIGHT / 22, SCREEN_WIDTH / 10, SCREEN_HEIGHT / 16, "Nilgiri",203, 230, 2) ;

			// Karakoram       

	    SDL_Rect karakoram = { SCREEN_WIDTH / 22 + 200, SCREEN_HEIGHT / 22,SCREEN_WIDTH / 10, SCREEN_HEIGHT / 10 };
            loadFromFile("karakoram.png");

            // SDL_SetTextInputRect(&fillRect);
       
            SDL_RenderCopy(gRenderer,imageTexture,NULL,&karakoram);
            SDL_DestroyTexture(imageTexture);            
            // SDL_SetTextInputRect(&fillRect);
       
            
            
            // disptext(gRenderer, SCREEN_WIDTH / 22 + 200, SCREEN_HEIGHT / 22, SCREEN_WIDTH / 10, SCREEN_HEIGHT / 16, "Karakoram",203, 230, 2 ) ;
            
            
            
            
            // Aravali
	    SDL_Rect aravali = { SCREEN_WIDTH / 22 + 400, SCREEN_HEIGHT / 22, SCREEN_WIDTH / 10, SCREEN_HEIGHT / 10 };

            // SDL_SetTextInputRect(&fillRect);
       
            loadFromFile("aravali.png");

            // SDL_SetTextInputRect(&fillRect);
       
            SDL_RenderCopy(gRenderer,imageTexture,NULL,&aravali);
            SDL_DestroyTexture(imageTexture);            
            
            // disptext(gRenderer, SCREEN_WIDTH / 22 + 400, SCREEN_HEIGHT / 22, SCREEN_WIDTH / 10, SCREEN_HEIGHT / 16, "Aravali",203, 230, 2 ) ;
            

            // Jwala
	    SDL_Rect jwala = { SCREEN_WIDTH / 22 + 740, SCREEN_HEIGHT / 22, SCREEN_WIDTH / 10, SCREEN_HEIGHT / 10};
            loadFromFile("jwalamukhi.png");

            // SDL_SetTextInputRect(&fillRect);
       
            SDL_RenderCopy(gRenderer,imageTexture,NULL,&jwala);  
            SDL_DestroyTexture(imageTexture);
            
            
            // disptext(gRenderer, SCREEN_WIDTH / 22 + 800, SCREEN_HEIGHT / 22, SCREEN_WIDTH / 10, SCREEN_HEIGHT / 16, "Jwala",203, 230, 2 ) ;

            // Kumaon
            SDL_Rect kumaon = { SCREEN_WIDTH / 22 + 740, SCREEN_HEIGHT / 22+140, SCREEN_WIDTH / 10, SCREEN_HEIGHT / 10 };
            loadFromFile("kumaon.png");

            // SDL_SetTextInputRect(&fillRect);
       
            SDL_RenderCopy(gRenderer,imageTexture,NULL,&kumaon);
            SDL_DestroyTexture(imageTexture);

            // SDL_SetTextInputRect(&fillRect);
       

            // disptext(gRenderer, SCREEN_WIDTH / 22 + 800, SCREEN_HEIGHT / 22 + 100, SCREEN_WIDTH / 10, SCREEN_HEIGHT / 16, "Kumaon",203, 230, 2 ) ;
            
            
            // Vidyanchal
            SDL_Rect vidyanchal = { SCREEN_WIDTH / 22 + 740, SCREEN_HEIGHT / 22+250, SCREEN_WIDTH / 10, SCREEN_HEIGHT / 10 };
            loadFromFile("vidyanchal.png");

            // SDL_SetTextInputRect(&fillRect);
       
            SDL_RenderCopy(gRenderer,imageTexture,NULL,&vidyanchal);
            SDL_DestroyTexture(imageTexture);


            // disptext(gRenderer, SCREEN_WIDTH / 22 + 800, SCREEN_HEIGHT / 22 + 250, SCREEN_WIDTH / 10, SCREEN_HEIGHT / 16, "Vidyanchal",203, 230, 2 ) ;
            
             // Delhi - 16
            SDL_Rect deli16 = { SCREEN_WIDTH / 22 + 400, SCREEN_HEIGHT / 22+135, SCREEN_WIDTH / 10, SCREEN_HEIGHT / 8 };
            loadFromFile("deli16.png"); 

            // SDL_SetTextInputRect(&fillRect);
       
            SDL_RenderCopy(gRenderer,imageTexture,NULL,&deli16);
            
            
            // disptext(gRenderer, SCREEN_WIDTH / 22 + 400, SCREEN_HEIGHT / 22 + 120, SCREEN_WIDTH / 10, SCREEN_HEIGHT / 16, "Dilli-16" ,255, 255, 255) ;

            // Tennis Court

            SDL_Rect tennisCourt = { SCREEN_WIDTH / 22 + 200, SCREEN_HEIGHT / 22+200, SCREEN_WIDTH / 8, SCREEN_HEIGHT / 12 };
            loadFromFile("tennis_court.png");
            SDL_RenderCopy(gRenderer,imageTexture,NULL,&tennisCourt);
            SDL_DestroyTexture(imageTexture);
       
            
            
            
            
            
            // Volley Ball Court
           	SDL_Rect volleyBallCourt = { SCREEN_WIDTH / 22 + 350, SCREEN_HEIGHT / 22+195, SCREEN_WIDTH / 8, SCREEN_HEIGHT / 10};
            loadFromFile("volleyball.png");
            SDL_RenderCopy(gRenderer,imageTexture,NULL,&volleyBallCourt);
            SDL_DestroyTexture(imageTexture);

            // SDL_SetTextInputRect(&fillRect);
       
            
            
            
            
            
            

            // Shivalik

            SDL_Rect shivalik = { SCREEN_WIDTH / 22 + 365, SCREEN_HEIGHT / 22+270, SCREEN_WIDTH / 10, SCREEN_HEIGHT / 10 };
            loadFromFile("shivalik.png");
            // SDL_SetTextInputRect(&fillRect);
       
            SDL_RenderCopy(gRenderer,imageTexture,NULL,&shivalik);
            SDL_DestroyTexture(imageTexture);
            
            
            
            

            // Zanskar

            SDL_Rect zanskar = { SCREEN_WIDTH / 22 + 240, SCREEN_HEIGHT / 22+270, SCREEN_WIDTH / 10, SCREEN_HEIGHT / 10 };
            loadFromFile("zanskar.png");

            // SDL_SetTextInputRect(&fillRect);
       
            SDL_RenderCopy(gRenderer,imageTexture,NULL,&zanskar); 
            SDL_DestroyTexture(imageTexture);          

            
            // disptext(gRenderer, SCREEN_WIDTH / 22 + 200, SCREEN_HEIGHT / 22+300, SCREEN_WIDTH / 10, SCREEN_HEIGHT / 16, "Zanskar",203, 230, 2 ) ;
            

            // SAC

            SDL_Rect sac = { SCREEN_WIDTH / 22, SCREEN_HEIGHT / 22+270, SCREEN_WIDTH / 16, SCREEN_HEIGHT / 10 };
            SDL_SetRenderDrawColor( gRenderer,164, 191, 31, 0xFF  ); 

            // SDL_SetTextInputRect(&fillRect);
       
            SDL_RenderFillRect( gRenderer, &sac );
            
            
            
            // disptext(gRenderer, SCREEN_WIDTH / 22, SCREEN_HEIGHT / 22+270, SCREEN_WIDTH / 16, SCREEN_HEIGHT / 10, "SAC",255,255,255 ) ;



			// Masala Mix
	    SDL_Rect masalaMix = { SCREEN_WIDTH / 22+230,  SCREEN_HEIGHT / 22+280+SCREEN_HEIGHT / 16, SCREEN_WIDTH / 12, SCREEN_HEIGHT / 8 };
            loadFromFile("masalamix.png"); 

            SDL_RenderCopy(gRenderer,imageTexture,NULL,&masalaMix);
            SDL_DestroyTexture(imageTexture);
            
            
            
            // disptext(gRenderer,  SCREEN_WIDTH / 22+200,  SCREEN_HEIGHT / 22+310+SCREEN_HEIGHT / 16, SCREEN_WIDTH / 12, SCREEN_HEIGHT / 16, "Masala Mix",252, 186, 3 ) ;



            // Rajdhani
			SDL_Rect rajdhani = { SCREEN_WIDTH / 22+200+SCREEN_WIDTH / 12,SCREEN_HEIGHT / 22+290+SCREEN_HEIGHT / 16, SCREEN_WIDTH / 12, SCREEN_HEIGHT / 12 };
            loadFromFile("rajdhani.png");
            SDL_RenderCopy(gRenderer,imageTexture,NULL,&rajdhani);
            SDL_DestroyTexture(imageTexture);
            
            
            // disptext(gRenderer,  SCREEN_WIDTH / 22+210+SCREEN_WIDTH / 12,SCREEN_HEIGHT / 22+310+SCREEN_HEIGHT / 16, SCREEN_WIDTH / 12, SCREEN_HEIGHT / 16 , "Rajdhani",255,255,255 ) ;
            
            

            // Chaayos
	    SDL_Rect chaayos = { SCREEN_WIDTH / 22+200+2*SCREEN_WIDTH / 12, SCREEN_HEIGHT / 22+300+SCREEN_HEIGHT / 16, SCREEN_WIDTH / 14, SCREEN_HEIGHT / 14 };
            loadFromFile("chaayos.png");
            SDL_RenderCopy(gRenderer,imageTexture,NULL,&chaayos);
            SDL_DestroyTexture(imageTexture);
            
            
            // disptext(gRenderer,  SCREEN_WIDTH / 22+220+2*SCREEN_WIDTH / 12, SCREEN_HEIGHT / 22+310+SCREEN_HEIGHT / 16, SCREEN_WIDTH / 12, SCREEN_HEIGHT / 16, "Chaayos",255,255,255 ) ;
            
            

            // IIT-D Hospital
			SDL_Rect hospital = {  SCREEN_WIDTH / 22+200, SCREEN_HEIGHT / 22+410+SCREEN_HEIGHT / 16, SCREEN_WIDTH / 6, SCREEN_HEIGHT / 8 };
            SDL_SetRenderDrawColor( gRenderer, 255, 0, 0, 0xFF ); 
            loadFromFile("iitd-hospital.png");
            SDL_RenderCopy(gRenderer,imageTexture,NULL,&hospital);
            SDL_DestroyTexture(imageTexture);


                


            // Bharti - School of AI
	    SDL_Rect bharti = {  SCREEN_WIDTH / 22+200 , SCREEN_HEIGHT / 22+430+SCREEN_HEIGHT / 16+  SCREEN_HEIGHT / 10, SCREEN_WIDTH / 6, SCREEN_HEIGHT / 8 };
            loadFromFile("bharti.png");
            SDL_RenderCopy(gRenderer,imageTexture,NULL,&bharti);
            SDL_DestroyTexture(imageTexture);
            // SDL_SetRenderDrawColor( gRenderer, 164, 191, 31, 0xFF ); 

            // SDL_RenderFillRect( gRenderer, &bharti );
            
            // disptext(gRenderer,  SCREEN_WIDTH / 22+200 , SCREEN_HEIGHT / 22+430+SCREEN_HEIGHT / 16+  SCREEN_HEIGHT / 10, SCREEN_WIDTH / 8, SCREEN_HEIGHT / 10 , "Bharti Building",255,255,255 ) ;
// 
            // Large ground 

            SDL_Rect largeGround = {  SCREEN_WIDTH / 22 , SCREEN_HEIGHT / 22+450, SCREEN_WIDTH /12, SCREEN_HEIGHT / 6 };
            loadFromFile("grass.png");
            SDL_RenderCopy(gRenderer,imageTexture,NULL,&largeGround);
            SDL_DestroyTexture(imageTexture);

            SDL_Rect gtree1 = {8 , SCREEN_HEIGHT / 22+400, 100,100};
            loadFromFile("tree-top.png");
            SDL_RenderCopy(gRenderer,imageTexture,NULL,&gtree1);  
            SDL_DestroyTexture(imageTexture); 


            SDL_Rect gtree2 = {8 , SCREEN_HEIGHT / 22+400+30, 100,100};
            loadFromFile("tree-top.png");
            SDL_RenderCopy(gRenderer,imageTexture,NULL,&gtree2); 
            SDL_DestroyTexture(imageTexture);


            SDL_Rect gtree3 = {8 , SCREEN_HEIGHT / 22+400+60, 100,100};
            loadFromFile("tree-top.png");
            SDL_RenderCopy(gRenderer,imageTexture,NULL,&gtree3); 
            SDL_DestroyTexture(imageTexture);

            SDL_Rect gtree4 = {8 , SCREEN_HEIGHT / 22+400+90, 100,100};
            loadFromFile("tree-top.png");
            SDL_RenderCopy(gRenderer,imageTexture,NULL,&gtree4); 
            SDL_DestroyTexture(imageTexture);

            SDL_Rect gtree5 = {8 , SCREEN_HEIGHT / 22+400+120, 100,100};
            loadFromFile("tree-top.png");
            SDL_RenderCopy(gRenderer,imageTexture,NULL,&gtree5);   
            SDL_DestroyTexture(imageTexture);


            SDL_Rect gtree6 = {8 , SCREEN_HEIGHT / 22+400+150, 100,100};
            loadFromFile("tree-top.png");
            SDL_RenderCopy(gRenderer,imageTexture,NULL,&gtree6); 
            SDL_DestroyTexture(imageTexture);


            SDL_Rect gtree7 = {8+SCREEN_WIDTH /12+22 , SCREEN_HEIGHT / 22+400, 100,100};
            loadFromFile("tree-top.png");
            SDL_RenderCopy(gRenderer,imageTexture,NULL,&gtree7);  
            SDL_DestroyTexture(imageTexture); 


            SDL_Rect gtree8 = {8+SCREEN_WIDTH /12+22 , SCREEN_HEIGHT / 22+400+30, 100,100};
            loadFromFile("tree-top.png");
            SDL_RenderCopy(gRenderer,imageTexture,NULL,&gtree8); 
            SDL_DestroyTexture(imageTexture);


            SDL_Rect gtree9 = {8+SCREEN_WIDTH /12+22 , SCREEN_HEIGHT / 22+400+60, 100,100};
            loadFromFile("tree-top.png");
            SDL_RenderCopy(gRenderer,imageTexture,NULL,&gtree9); 
            SDL_DestroyTexture(imageTexture);

            SDL_Rect gtree10 = {8+SCREEN_WIDTH /12+22 , SCREEN_HEIGHT / 22+400+90, 100,100};
            loadFromFile("tree-top.png");
            SDL_RenderCopy(gRenderer,imageTexture,NULL,&gtree10); 
            SDL_DestroyTexture(imageTexture);

            SDL_Rect gtree11 = {8+SCREEN_WIDTH /12+22 , SCREEN_HEIGHT / 22+400+120, 100,100};
            loadFromFile("tree-top.png");
            SDL_RenderCopy(gRenderer,imageTexture,NULL,&gtree11); 
            SDL_DestroyTexture(imageTexture);  


            SDL_Rect gtree12 = {8+SCREEN_WIDTH /12+22 , SCREEN_HEIGHT / 22+400+150, 100,100};
            loadFromFile("tree-top.png");
            SDL_RenderCopy(gRenderer,imageTexture,NULL,&gtree12);
            SDL_DestroyTexture(imageTexture); 


            // SDL_SetRenderDrawColor( gRenderer, 92, 8, 8, 0xFF ); 

            // SDL_RenderFillRect( gRenderer, &largeGround );
            
            
            
            // disptext(gRenderer,  SCREEN_WIDTH / 22 , SCREEN_HEIGHT / 22+450, SCREEN_WIDTH / 10, SCREEN_HEIGHT / 4 , "Large Ground",255,255,255 ) ;

            // Staff canteen

            SDL_Rect staffCanteen = {  SCREEN_WIDTH / 22 , SCREEN_HEIGHT / 22+470 + SCREEN_HEIGHT / 4, SCREEN_WIDTH / 10, SCREEN_HEIGHT / 10 };
            loadFromFile("staffcanteen.png");            
            SDL_RenderCopy(gRenderer,imageTexture,NULL,&staffCanteen);
            SDL_DestroyTexture(imageTexture);
            
            
            // disptext(gRenderer,  SCREEN_WIDTH / 22 , SCREEN_HEIGHT / 22+470 + SCREEN_HEIGHT / 4, SCREEN_WIDTH / 16, SCREEN_HEIGHT / 16  , "Staff Canteen",255,255,255 ) ;


            // LHC

            SDL_Rect LHC = {  SCREEN_WIDTH / 22 , SCREEN_HEIGHT / 22+490 + SCREEN_HEIGHT / 4 +  SCREEN_HEIGHT / 16, SCREEN_WIDTH / 10, SCREEN_HEIGHT / 10 };
            loadFromFile("lecturehall.png");
            SDL_RenderCopy(gRenderer,imageTexture,NULL,&LHC);
            SDL_DestroyTexture(imageTexture);

            // SDL_RenderFillRect( gRenderer, &LHC);
            
            // dogra hall

            SDL_Rect dograHall = {  SCREEN_WIDTH / 22+260 , SCREEN_HEIGHT / 22+490 + SCREEN_HEIGHT / 4 +  SCREEN_HEIGHT / 16, SCREEN_WIDTH / 8, SCREEN_HEIGHT / 8 };
            loadFromFile("dograhall.png");
            SDL_RenderCopy(gRenderer,imageTexture,NULL,&dograHall);
            SDL_DestroyTexture(imageTexture);

            // csc

            SDL_Rect csc ={ SCREEN_WIDTH / 22+300+5*SCREEN_WIDTH / 12, SCREEN_HEIGHT / 22+520 + SCREEN_HEIGHT / 4+ SCREEN_HEIGHT / 16+40, SCREEN_WIDTH / 10, SCREEN_HEIGHT / 8 };
            loadFromFile("csc.png");
            SDL_RenderCopy(gRenderer,imageTexture,NULL,&csc);
            SDL_DestroyTexture(imageTexture);
            
            // disptext(gRenderer,  SCREEN_WIDTH / 22 , SCREEN_HEIGHT / 22+490 + SCREEN_HEIGHT / 4 +  SCREEN_HEIGHT / 16, SCREEN_WIDTH / 10, SCREEN_HEIGHT / 10  , "LHC",255,255,255 ) ;



            // Satpura

            SDL_Rect satpura ={ SCREEN_WIDTH / 22+230+3*SCREEN_WIDTH / 12, SCREEN_HEIGHT / 22+310+SCREEN_HEIGHT / 16+40, SCREEN_WIDTH / 10, SCREEN_HEIGHT / 10 };
            loadFromFile("satpura.png");
            SDL_RenderCopy(gRenderer,imageTexture,NULL,&satpura); 
            SDL_DestroyTexture(imageTexture);


            // girnar

            SDL_Rect girnar={ SCREEN_WIDTH / 22+160+3*SCREEN_WIDTH / 12, SCREEN_HEIGHT / 22+310+SCREEN_HEIGHT / 16+140, SCREEN_WIDTH / 10, SCREEN_HEIGHT / 10 };
            loadFromFile("girnar.png");
            // SDL_SetTextInputRect(&fillRect);
       
            SDL_RenderCopy(gRenderer,imageTexture,NULL,&girnar); 
            SDL_DestroyTexture(imageTexture);

            // udaigiri

            SDL_Rect udaigiri={ SCREEN_WIDTH / 22+160+3*SCREEN_WIDTH / 12, SCREEN_HEIGHT / 22+310+SCREEN_HEIGHT / 16+110+SCREEN_HEIGHT / 10, SCREEN_WIDTH / 10, SCREEN_HEIGHT / 10 };
            loadFromFile("udaigiri.png");
            // SDL_SetTextInputRect(&fillRect);
       
            SDL_RenderCopy(gRenderer,imageTexture,NULL,&udaigiri);
            SDL_DestroyTexture(imageTexture); 


            
            
            // disptext(gRenderer,  SCREEN_WIDTH / 22+230+3*SCREEN_WIDTH / 12, SCREEN_HEIGHT / 22+310+SCREEN_HEIGHT / 16+40, SCREEN_WIDTH / 10, SCREEN_HEIGHT / 16  , "Satpura",203, 230, 2  ) ;



            // Shiru's cafe

            SDL_Rect shiru ={ SCREEN_WIDTH / 22+220+2*SCREEN_WIDTH / 12, SCREEN_HEIGHT / 22+470 + SCREEN_HEIGHT / 4, SCREEN_WIDTH / 10, SCREEN_HEIGHT / 10 };
            loadFromFile("shirucafe.png");
            SDL_RenderCopy(gRenderer,imageTexture,NULL,&shiru);
            SDL_DestroyTexture(imageTexture);
            
            
            // disptext(gRenderer,  SCREEN_WIDTH / 22+220+2*SCREEN_WIDTH / 12, SCREEN_HEIGHT / 22+470 + SCREEN_HEIGHT / 4, SCREEN_WIDTH / 12, SCREEN_HEIGHT / 16  , "Shiru's Cafe",163, 163, 162 ) ;
            
            

            // Amul
            SDL_Rect amul ={ SCREEN_WIDTH / 22+230+3*SCREEN_WIDTH / 12, SCREEN_HEIGHT / 22+470 + SCREEN_HEIGHT / 4, SCREEN_WIDTH / 10, SCREEN_HEIGHT / 10 };
            loadFromFile("amul.png"); 

            SDL_RenderCopy(gRenderer,imageTexture,NULL,&amul);
            SDL_DestroyTexture(imageTexture);
            
            
            
            

            // Nescafe
            SDL_Rect nescafe ={ SCREEN_WIDTH / 22+260+4*SCREEN_WIDTH / 12, SCREEN_HEIGHT / 22+420 + SCREEN_HEIGHT / 4, SCREEN_WIDTH / 9, SCREEN_HEIGHT / 4 };
            loadFromFile("nescafe.png");
            SDL_RenderCopy(gRenderer,imageTexture,NULL,&nescafe);
            SDL_DestroyTexture(imageTexture);        
            


            // CCD 


            SDL_Rect ccd ={ SCREEN_WIDTH / 22+300+5*SCREEN_WIDTH / 12, SCREEN_HEIGHT / 22+500 + SCREEN_HEIGHT / 4, SCREEN_WIDTH / 8, SCREEN_HEIGHT / 6 };
            loadFromFile("ccd.png");
            SDL_RenderCopy(gRenderer,imageTexture,NULL,&ccd);
            SDL_DestroyTexture(imageTexture);
            
            
            
            
            // disptext(gRenderer,   SCREEN_WIDTH / 22+300+5*SCREEN_WIDTH / 12, SCREEN_HEIGHT / 22+440 + SCREEN_HEIGHT / 4, SCREEN_WIDTH / 12, SCREEN_HEIGHT / 16 , "Cafe Coffee Day",255,255,255 ) ;

            
            char* str = "Dogra hall";
            // std::vector<char> cstr(str.c_str(), str.c_str() + str.size() + 1);
            // 
            // disptext(gRenderer,   SCREEN_WIDTH / 22+310+5*SCREEN_WIDTH / 12, SCREEN_HEIGHT / 22+450 + SCREEN_HEIGHT / 4+ SCREEN_HEIGHT / 16+40, SCREEN_WIDTH / 16, SCREEN_HEIGHT / 20, "Dogra Hall",255,255,255 ) ;
            
            
            // central library

            SDL_Rect clibrary = {SCREEN_WIDTH / 22+220+2*SCREEN_WIDTH / 12, SCREEN_HEIGHT / 22+500 + SCREEN_HEIGHT / 4+ SCREEN_HEIGHT / 16, SCREEN_WIDTH / 6, SCREEN_HEIGHT / 12 +80};
            loadFromFile("centrallibrary.png");
            SDL_RenderCopy(gRenderer,imageTexture,NULL,&clibrary);
            SDL_DestroyTexture(imageTexture);

            // Main building

            SDL_Rect mainBuilding ={  SCREEN_WIDTH / 22+850+2*SCREEN_WIDTH / 12, SCREEN_HEIGHT / 22+500 + SCREEN_HEIGHT / 4+ SCREEN_HEIGHT / 16, SCREEN_WIDTH / 6, SCREEN_HEIGHT / 12 +80};
            loadFromFile("mainbuilding.png");
            SDL_RenderCopy(gRenderer,imageTexture,NULL,&mainBuilding);
            SDL_DestroyTexture(imageTexture);
            // SDL_SetRenderDrawColor( gRenderer,164, 191, 31, 0xFF ); 
            // SDL_RenderFillRect( gRenderer, &mainBuilding); 


            
            // disptext(gRenderer,  SCREEN_WIDTH / 22+220+2*SCREEN_WIDTH / 12, SCREEN_HEIGHT / 22+540 + SCREEN_HEIGHT / 4+ SCREEN_HEIGHT / 16+40, SCREEN_WIDTH / 4, SCREEN_HEIGHT / 12 , "Main Building",255,255,255 ) ;

            // ROADS

            // SAC CIRCLE ROAD
            SDL_Rect sacCircle ={  SCREEN_WIDTH / 22+70,SCREEN_HEIGHT / 22+200, SCREEN_WIDTH / 5, SCREEN_HEIGHT / 5};
            loadFromFile("saccircle.png");
            SDL_RenderCopy(gRenderer,imageTexture,NULL,&sacCircle);
            SDL_DestroyTexture(imageTexture);

            SDL_Rect vr1 ={  SCREEN_WIDTH / 22+70,SCREEN_HEIGHT / 22+290, SCREEN_WIDTH / 5, SCREEN_HEIGHT / 5};
            loadFromFile("verticalroad.png");
            SDL_RenderCopy(gRenderer,imageTexture,NULL,&vr1);
            SDL_DestroyTexture(imageTexture);

            SDL_Rect vr2 ={  SCREEN_WIDTH / 22+70,SCREEN_HEIGHT / 22+380, SCREEN_WIDTH / 5, SCREEN_HEIGHT / 5};
            loadFromFile("verticalroad.png");
            SDL_RenderCopy(gRenderer,imageTexture,NULL,&vr2);
            SDL_DestroyTexture(imageTexture);

            SDL_Rect vr3 ={  SCREEN_WIDTH / 22+70,SCREEN_HEIGHT / 22+470, SCREEN_WIDTH / 5, SCREEN_HEIGHT / 5};
            loadFromFile("verticalroad.png");
            SDL_RenderCopy(gRenderer,imageTexture,NULL,&vr3);
            SDL_DestroyTexture(imageTexture);
		

            SDL_Rect vr4 ={  SCREEN_WIDTH / 22+70,SCREEN_HEIGHT / 22+560, SCREEN_WIDTH / 5, SCREEN_HEIGHT / 5};
            loadFromFile("verticalroad.png");
            SDL_RenderCopy(gRenderer,imageTexture,NULL,&vr4);
            SDL_DestroyTexture(imageTexture);

            SDL_Rect vr5 ={  SCREEN_WIDTH / 22+70,SCREEN_HEIGHT / 22+650, SCREEN_WIDTH / 5, SCREEN_HEIGHT / 5};
            loadFromFile("verticalroad.png");
            SDL_RenderCopy(gRenderer,imageTexture,NULL,&vr5);
            SDL_DestroyTexture(imageTexture);

            SDL_Rect vr6 ={  SCREEN_WIDTH / 22+70,SCREEN_HEIGHT / 22+710, SCREEN_WIDTH / 5, SCREEN_HEIGHT / 4};
            loadFromFile("verticalroad.png");
            SDL_RenderCopy(gRenderer,imageTexture,NULL,&vr6);
            SDL_DestroyTexture(imageTexture);



            // SDL_Rect vr6 ={  SCREEN_WIDTH / 22+70,SCREEN_HEIGHT / 22+110, SCREEN_WIDTH / 5, SCREEN_HEIGHT / 5};
            // loadFromFile("verticalroad2.png");
            // SDL_RenderCopy(gRenderer,imageTexture,NULL,&vr6);

	
            SDL_Rect tp1 ={  SCREEN_WIDTH / 22+70,SCREEN_HEIGHT / 22+96, SCREEN_WIDTH / 5, SCREEN_HEIGHT / 5};
            loadFromFile("tpoint.png");
            SDL_RenderCopy(gRenderer,imageTexture,NULL,&tp1);  
            SDL_DestroyTexture(imageTexture);      


            SDL_Rect hr1 = {SCREEN_WIDTH / 22+350,SCREEN_HEIGHT / 22+96, SCREEN_WIDTH / 5, SCREEN_HEIGHT / 5};

            loadFromFile("horizontalroad.png");
            SDL_RenderCopy(gRenderer,imageTexture,NULL,&hr1);
            SDL_DestroyTexture(imageTexture);

            SDL_Rect hr2 = {SCREEN_WIDTH / 22+350+SCREEN_WIDTH / 5,SCREEN_HEIGHT / 22+96, SCREEN_WIDTH / 5, SCREEN_HEIGHT / 5};

            loadFromFile("horizontalroad.png");
            SDL_RenderCopy(gRenderer,imageTexture,NULL,&hr2);
            SDL_DestroyTexture(imageTexture);


            SDL_Rect hr3 = {SCREEN_WIDTH / 22-100,SCREEN_HEIGHT / 22+96, SCREEN_WIDTH / 5, SCREEN_HEIGHT / 5};

            loadFromFile("horizontalroad.png");
            SDL_RenderCopy(gRenderer,imageTexture,NULL,&hr3);
            SDL_DestroyTexture(imageTexture);


            SDL_Rect hr4 = {SCREEN_WIDTH / 22+150,SCREEN_HEIGHT / 22+200, SCREEN_WIDTH / 5, SCREEN_HEIGHT / 5};

            loadFromFile("horizontalroad2.png");
            SDL_RenderCopy(gRenderer,imageTexture,NULL,&hr4);
            SDL_DestroyTexture(imageTexture);


            SDL_Rect hr5 = {SCREEN_WIDTH / 22+150+95,SCREEN_HEIGHT / 22+200, SCREEN_WIDTH / 5, SCREEN_HEIGHT / 5};

            loadFromFile("horizontalroad2.png");
            SDL_RenderCopy(gRenderer,imageTexture,NULL,&hr5);
            SDL_DestroyTexture(imageTexture);

            SDL_Rect hr6 = {SCREEN_WIDTH / 22+150+95+95,SCREEN_HEIGHT / 22+200, SCREEN_WIDTH / 5, SCREEN_HEIGHT / 5};

            loadFromFile("horizontalroad2.png");
            SDL_RenderCopy(gRenderer,imageTexture,NULL,&hr6);
            SDL_DestroyTexture(imageTexture);


            SDL_Rect hr7 = {SCREEN_WIDTH / 22+150+95+95+95,SCREEN_HEIGHT / 22+200, SCREEN_WIDTH / 5, SCREEN_HEIGHT / 5};

            loadFromFile("horizontalroad2.png");
            SDL_RenderCopy(gRenderer,imageTexture,NULL,&hr7);
            SDL_DestroyTexture(imageTexture);



            SDL_Rect hr8 = {SCREEN_WIDTH / 22+150,SCREEN_HEIGHT / 22+200+430, SCREEN_WIDTH / 5, SCREEN_HEIGHT / 5};

            loadFromFile("horizontalroad2.png");
            SDL_RenderCopy(gRenderer,imageTexture,NULL,&hr8);
            SDL_DestroyTexture(imageTexture);

            SDL_Rect hr9 = {SCREEN_WIDTH / 22+150+95,SCREEN_HEIGHT / 22+200+430, SCREEN_WIDTH / 5, SCREEN_HEIGHT / 5};

            loadFromFile("horizontalroad2.png");
            SDL_RenderCopy(gRenderer,imageTexture,NULL,&hr9);
            SDL_DestroyTexture(imageTexture);


            SDL_Rect hr10 = {SCREEN_WIDTH / 22+150+95+95,SCREEN_HEIGHT / 22+200+430, SCREEN_WIDTH / 5, SCREEN_HEIGHT / 5};

            loadFromFile("horizontalroad2.png");
            SDL_RenderCopy(gRenderer,imageTexture,NULL,&hr10);
            SDL_DestroyTexture(imageTexture);

            SDL_Rect hr11 = {SCREEN_WIDTH / 22+150+95+95+95,SCREEN_HEIGHT / 22+200+430, SCREEN_WIDTH / 5, SCREEN_HEIGHT / 5};

            loadFromFile("horizontalroad2.png");
            SDL_RenderCopy(gRenderer,imageTexture,NULL,&hr11);
            SDL_DestroyTexture(imageTexture);

            SDL_Rect hr12 = {SCREEN_WIDTH / 22+50,SCREEN_HEIGHT / 22+200+430, SCREEN_WIDTH / 5, SCREEN_HEIGHT / 5};

            loadFromFile("horizontalroad2.png");
            SDL_RenderCopy(gRenderer,imageTexture,NULL,&hr12);
            SDL_DestroyTexture(imageTexture);

            SDL_Rect hr13 = {SCREEN_WIDTH / 22+10,SCREEN_HEIGHT / 22+200+430, SCREEN_WIDTH / 5, SCREEN_HEIGHT / 5};

            loadFromFile("horizontalroad2.png");
            SDL_RenderCopy(gRenderer,imageTexture,NULL,&hr13);
            SDL_DestroyTexture(imageTexture);

            SDL_Rect hr14 = {SCREEN_WIDTH / 22+150+95+95+95+95,SCREEN_HEIGHT / 22+200+430, SCREEN_WIDTH / 5, SCREEN_HEIGHT / 5};

            loadFromFile("horizontalroad2.png");
            SDL_RenderCopy(gRenderer,imageTexture,NULL,&hr14);
            SDL_DestroyTexture(imageTexture);

            SDL_Rect hr15 = {SCREEN_WIDTH / 22+150+95+95+95+95,SCREEN_HEIGHT / 22+200+430, SCREEN_WIDTH / 5, SCREEN_HEIGHT / 5};

            loadFromFile("horizontalroad2.png");
            SDL_RenderCopy(gRenderer,imageTexture,NULL,&hr15);
            SDL_DestroyTexture(imageTexture);


            SDL_Rect hr16 = {SCREEN_WIDTH / 22+150+95+95+95+95+95,SCREEN_HEIGHT / 22+200+430, SCREEN_WIDTH / 5, SCREEN_HEIGHT / 5};

            loadFromFile("horizontalroad2.png");
            SDL_RenderCopy(gRenderer,imageTexture,NULL,&hr16);
            SDL_DestroyTexture(imageTexture);

            SDL_Rect hr17 = {SCREEN_WIDTH / 22,SCREEN_HEIGHT / 22+200+430+240, SCREEN_WIDTH / 5, SCREEN_HEIGHT / 5};

            loadFromFile("horizontalroad2.png");
            SDL_RenderCopy(gRenderer,imageTexture,NULL,&hr17);
            SDL_DestroyTexture(imageTexture);


            SDL_Rect hr18 = {SCREEN_WIDTH / 22+95,SCREEN_HEIGHT / 22+200+430+240, SCREEN_WIDTH / 5, SCREEN_HEIGHT / 5};

            loadFromFile("horizontalroad2.png");
            SDL_RenderCopy(gRenderer,imageTexture,NULL,&hr18);
            SDL_DestroyTexture(imageTexture);


            SDL_Rect hr19 = {SCREEN_WIDTH / 22+190,SCREEN_HEIGHT / 22+200+430+240, SCREEN_WIDTH / 5, SCREEN_HEIGHT / 5};

            loadFromFile("horizontalroad2.png");
            SDL_RenderCopy(gRenderer,imageTexture,NULL,&hr19);
            SDL_DestroyTexture(imageTexture);


            SDL_Rect hr20 = {SCREEN_WIDTH / 22+285,SCREEN_HEIGHT / 22+200+430+240, SCREEN_WIDTH / 5, SCREEN_HEIGHT / 5};

            loadFromFile("horizontalroad2.png");
            SDL_RenderCopy(gRenderer,imageTexture,NULL,&hr20);
            SDL_DestroyTexture(imageTexture);


            SDL_Rect hr21 = {SCREEN_WIDTH / 22+370,SCREEN_HEIGHT / 22+200+430+240, SCREEN_WIDTH / 5, SCREEN_HEIGHT / 5};

            loadFromFile("horizontalroad2.png");
            SDL_RenderCopy(gRenderer,imageTexture,NULL,&hr21);
            SDL_DestroyTexture(imageTexture);

            SDL_Rect hr22 = {SCREEN_WIDTH / 22+465,SCREEN_HEIGHT / 22+200+430+240, SCREEN_WIDTH / 5, SCREEN_HEIGHT / 5};

            loadFromFile("horizontalroad2.png");
            SDL_RenderCopy(gRenderer,imageTexture,NULL,&hr22);
            SDL_DestroyTexture(imageTexture);


            SDL_Rect hr23 = {SCREEN_WIDTH / 22+560,SCREEN_HEIGHT / 22+200+430+240, SCREEN_WIDTH / 5, SCREEN_HEIGHT / 5};

            loadFromFile("horizontalroad2.png");
            SDL_RenderCopy(gRenderer,imageTexture,NULL,&hr23);
            SDL_DestroyTexture(imageTexture);

            SDL_Rect hr24 = {SCREEN_WIDTH / 22+655,SCREEN_HEIGHT / 22+200+430+240, SCREEN_WIDTH / 5, SCREEN_HEIGHT / 5};

            loadFromFile("horizontalroad2.png");
            SDL_RenderCopy(gRenderer,imageTexture,NULL,&hr24);
            SDL_DestroyTexture(imageTexture);


            SDL_Rect vr7 = {SCREEN_WIDTH / 22+150+95+95+95+95+95+180,SCREEN_HEIGHT / 22+200+393, SCREEN_WIDTH / 5, SCREEN_HEIGHT / 5};

            loadFromFile("verticalroad.png");
            SDL_RenderCopy(gRenderer,imageTexture,NULL,&vr7);
            SDL_DestroyTexture(imageTexture);


            SDL_Rect vr8 = {SCREEN_WIDTH / 22+150+95+95+95+95+95+180,SCREEN_HEIGHT / 22+200+393+80, SCREEN_WIDTH / 5, SCREEN_HEIGHT / 5};

            loadFromFile("verticalroad.png");
            SDL_RenderCopy(gRenderer,imageTexture,NULL,&vr8);
            SDL_DestroyTexture(imageTexture);


            SDL_Rect vr9 = {SCREEN_WIDTH / 22+150+95+95+95+95+95+180,SCREEN_HEIGHT / 22+200+393+80+80, SCREEN_WIDTH / 5, SCREEN_HEIGHT / 5};

            loadFromFile("verticalroad.png");
            SDL_RenderCopy(gRenderer,imageTexture,NULL,&vr9);
            SDL_DestroyTexture(imageTexture);

            SDL_Rect vr10 = {SCREEN_WIDTH / 22+150+95+95+79+180,SCREEN_HEIGHT / 22+170, SCREEN_WIDTH / 5, SCREEN_HEIGHT / 5};

            loadFromFile("verticalroad.png");
            SDL_RenderCopy(gRenderer,imageTexture,NULL,&vr10);
            SDL_DestroyTexture(imageTexture);


            SDL_Rect vr11 = {SCREEN_WIDTH / 22+150+95+95+79+180,SCREEN_HEIGHT / 22+170+70, SCREEN_WIDTH / 5, SCREEN_HEIGHT / 5};

            loadFromFile("verticalroad.png");
            SDL_RenderCopy(gRenderer,imageTexture,NULL,&vr11);
            SDL_DestroyTexture(imageTexture);


            SDL_Rect vr12 = {SCREEN_WIDTH / 22+150+80+79+180,SCREEN_HEIGHT / 22+170, SCREEN_WIDTH / 5, SCREEN_HEIGHT / 5};

            loadFromFile("verticalroad.png");
            SDL_RenderCopy(gRenderer,imageTexture,NULL,&vr12);
            SDL_DestroyTexture(imageTexture);


            SDL_Rect vr13 = {SCREEN_WIDTH / 22+150+80+79+180,SCREEN_HEIGHT / 22+170+80, SCREEN_WIDTH / 5, SCREEN_HEIGHT / 5};

            loadFromFile("verticalroad.png");
            SDL_RenderCopy(gRenderer,imageTexture,NULL,&vr13);
            SDL_DestroyTexture(imageTexture);



            SDL_Rect vr14 = {SCREEN_WIDTH / 22+150+80+79+180,SCREEN_HEIGHT / 22+170+80+80, SCREEN_WIDTH / 5, SCREEN_HEIGHT / 5};

            loadFromFile("verticalroad.png");
            SDL_RenderCopy(gRenderer,imageTexture,NULL,&vr14);
            SDL_DestroyTexture(imageTexture);


            SDL_Rect vr15 = {SCREEN_WIDTH / 22+150+95+95+79+180,SCREEN_HEIGHT / 22+40, SCREEN_WIDTH / 5, SCREEN_HEIGHT / 5};

            loadFromFile("verticalroad.png");
            SDL_RenderCopy(gRenderer,imageTexture,NULL,&vr15);
            SDL_DestroyTexture(imageTexture);



            SDL_Rect vr16 = {SCREEN_WIDTH / 22+150+95+95+79+180,SCREEN_HEIGHT / 22+80, SCREEN_WIDTH / 5, SCREEN_HEIGHT / 5};

            loadFromFile("verticalroad.png");
            SDL_RenderCopy(gRenderer,imageTexture,NULL,&vr16);
            SDL_DestroyTexture(imageTexture);


            



            SDL_Rect hr26 = {SCREEN_WIDTH / 22+150+175,SCREEN_HEIGHT / 22+370, SCREEN_WIDTH / 5, SCREEN_HEIGHT / 5};

            loadFromFile("horizontalroad2.png");
            SDL_RenderCopy(gRenderer,imageTexture,NULL,&hr26);
            SDL_DestroyTexture(imageTexture);


            SDL_Rect hr27 = {SCREEN_WIDTH / 22+150+80,SCREEN_HEIGHT / 22+370, SCREEN_WIDTH / 5, SCREEN_HEIGHT / 5};

            loadFromFile("horizontalroad2.png");
            SDL_RenderCopy(gRenderer,imageTexture,NULL,&hr27);
            SDL_DestroyTexture(imageTexture);

            SDL_Rect hr28 = {SCREEN_WIDTH / 22+135,SCREEN_HEIGHT / 22+370, SCREEN_WIDTH / 5, SCREEN_HEIGHT / 5};

            loadFromFile("horizontalroad2.png");
            SDL_RenderCopy(gRenderer,imageTexture,NULL,&hr28);
            SDL_DestroyTexture(imageTexture);

            SDL_Rect hr29 = {SCREEN_WIDTH / 22+40,SCREEN_HEIGHT / 22+370, SCREEN_WIDTH / 5, SCREEN_HEIGHT / 5};

            loadFromFile("horizontalroad2.png");
            SDL_RenderCopy(gRenderer,imageTexture,NULL,&hr29);
            SDL_DestroyTexture(imageTexture);


            SDL_Rect hr30 = {SCREEN_WIDTH / 22+20,SCREEN_HEIGHT / 22+370, SCREEN_WIDTH / 5, SCREEN_HEIGHT / 5};

            loadFromFile("horizontalroad2.png");
            SDL_RenderCopy(gRenderer,imageTexture,NULL,&hr30);
            SDL_DestroyTexture(imageTexture);


            SDL_Rect hr31 = {SCREEN_WIDTH / 22+150+175,SCREEN_HEIGHT / 22+440, SCREEN_WIDTH / 5, SCREEN_HEIGHT / 5};

            loadFromFile("horizontalroad2.png");
            SDL_RenderCopy(gRenderer,imageTexture,NULL,&hr31);
            SDL_DestroyTexture(imageTexture);


            SDL_Rect vr17 = {SCREEN_WIDTH / 22+150+95+168,SCREEN_HEIGHT / 22+410, SCREEN_WIDTH / 5, SCREEN_HEIGHT / 5};

            loadFromFile("verticalroad.png");
            SDL_RenderCopy(gRenderer,imageTexture,NULL,&vr17);
            SDL_DestroyTexture(imageTexture);

            SDL_Rect vr18 = {SCREEN_WIDTH / 22+150+95+168,SCREEN_HEIGHT / 22+450, SCREEN_WIDTH / 5, SCREEN_HEIGHT / 5};

            loadFromFile("verticalroad.png");
            SDL_RenderCopy(gRenderer,imageTexture,NULL,&vr18);
            SDL_DestroyTexture(imageTexture);
///////////////////////////////////////////////////////////////////


            // SDL_Surface* textSurface = TTF_RenderText_Shaded(font, totalKilled,    foregroundColor, backgroundColor);


            SDL_SetRenderDrawColor( gRenderer,235, 52, 155, 0xFF );
            player1.renderPlayer();


            SDL_SetRenderDrawColor( gRenderer,92, 52, 235, 0xFF );
            player2.renderPlayer();


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
                                                        break;
                                                case SDLK_DOWN:
                                                        player1.move(KEY_PRESS_DOWN);
                                                        break;
                                                case SDLK_LEFT:
                                                        player1.move(KEY_PRESS_LEFT);
                                                        break;
                                                case SDLK_RIGHT:
                                                        player1.move(KEY_PRESS_RIGHT);
                                                        break;

                                        }
                                }
                                SDL_SetRenderDrawColor( gRenderer,235, 52, 155, 0xFF );
                                player1.renderPlayer();

                        }
        string s= "Player happiness:-"+to_string(player1.happiness);
        int n = s.length();
        char char_array1[n + 1];
        strcpy(char_array1, s.c_str());
        // disptext(gRenderer,  SCREEN_WIDTH-160,750,140,50, char_array1,235, 52, 155) ;

        s= "Player money:-"+to_string(player1.money);
        n = s.length();
        char char_array2[n + 1];
        strcpy(char_array2, s.c_str());
        // disptext(gRenderer,  SCREEN_WIDTH-160,700,140,50, char_array2,235, 52, 155) ;

        s= "Player knowledge:-"+to_string(player1.knowledge);
        n = s.length();
        char char_array3[n + 1];
        strcpy(char_array3, s.c_str());
        // disptext(gRenderer,  SCREEN_WIDTH-160,650,140,50, char_array3,235, 52, 155) ;

        s= "Player energy:-"+to_string(player1.energy);
        n = s.length();
        char char_array4[n + 1];
        strcpy(char_array4, s.c_str());
        // disptext(gRenderer,  SCREEN_WIDTH-160,600,140,50, char_array4,235, 52, 155) ;

        s= "Player health:-"+to_string(player1.health);
        n = s.length();
        char char_array5[n + 1];
        strcpy(char_array5, s.c_str());
        // disptext(gRenderer,  SCREEN_WIDTH-160,800,140,50, char_array5,235, 52, 155) ;













                SDL_RenderPresent(gRenderer);                     

                }
        }








	

	



	return 0;
}
