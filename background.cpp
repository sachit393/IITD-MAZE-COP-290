#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include <stdio.h>
#include <string>

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
        Player(int xP,int yP){
                health = 50;
                energy = 100;
                happiness = 50;
                money = 100;
                knowledge = 10;
                hasCycle = false;
                x = xP;
                y = yP;
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
                DrawCircle(gRenderer,x,y,PLAYER_RADIUS);
                DrawCircle(gRenderer,x,y,PLAYER_RADIUS-1);
                DrawCircle(gRenderer,x,y,PLAYER_RADIUS-2);
                DrawCircle(gRenderer,x,y,PLAYER_RADIUS-3);
                DrawCircle(gRenderer,x,y,PLAYER_RADIUS-4);
                DrawCircle(gRenderer,x,y,PLAYER_RADIUS-5);
                DrawCircle(gRenderer,x,y,PLAYER_RADIUS-6);
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
        gTexture = NULL;

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
                Player player1 = Player(20,20);
                Player player2 = Player(SCREEN_WIDTH-20,20);
		bool quit = false;

		SDL_Event e;

		while(!quit){

			SDL_SetRenderDrawColor(gRenderer,0x00,0x00,0x00,0x00);
			SDL_RenderClear(gRenderer);
			
			// Nilgiri
			SDL_Rect fillRect = { SCREEN_WIDTH / 22, SCREEN_HEIGHT / 22, SCREEN_WIDTH / 10, SCREEN_HEIGHT / 16 };
            SDL_SetRenderDrawColor( gRenderer, 52, 61, 236, 0xFF ); 

            SDL_RenderFillRect( gRenderer, &fillRect );
			// SDL_RenderCopy(gRenderer,gTexture, NULL, NULL);

			// Karakoram       

			SDL_Rect karakoram = { SCREEN_WIDTH / 22 + 200, SCREEN_HEIGHT / 22, SCREEN_WIDTH / 10, SCREEN_HEIGHT / 16 };
            SDL_SetRenderDrawColor( gRenderer, 52, 61, 236, 0xFF ); 

            // SDL_SetTextInputRect(&fillRect);
       
            SDL_RenderFillRect( gRenderer, &karakoram );			

            // Aravali
			SDL_Rect aravali = { SCREEN_WIDTH / 22 + 400, SCREEN_HEIGHT / 22, SCREEN_WIDTH / 10, SCREEN_HEIGHT / 16 };
            SDL_SetRenderDrawColor( gRenderer, 52, 61, 236, 0xFF ); 

            // SDL_SetTextInputRect(&fillRect);
       
            SDL_RenderFillRect( gRenderer, &aravali);	

            // Jwala
			SDL_Rect jwala = { SCREEN_WIDTH / 22 + 800, SCREEN_HEIGHT / 22, SCREEN_WIDTH / 10, SCREEN_HEIGHT / 16 };
            SDL_SetRenderDrawColor( gRenderer, 52, 61, 236, 0xFF ); 

            // SDL_SetTextInputRect(&fillRect);
       
            SDL_RenderFillRect( gRenderer, &jwala );	

            // Kumaon
            SDL_Rect kumaon = { SCREEN_WIDTH / 22 + 800, SCREEN_HEIGHT / 22+100, SCREEN_WIDTH / 10, SCREEN_HEIGHT / 16 };
            SDL_SetRenderDrawColor( gRenderer, 52, 61, 236, 0xFF ); 

            // SDL_SetTextInputRect(&fillRect);
       
            SDL_RenderFillRect( gRenderer, &kumaon );

            // Vidyanchal
            SDL_Rect vidyanchal = { SCREEN_WIDTH / 22 + 800, SCREEN_HEIGHT / 22+250, SCREEN_WIDTH / 10, SCREEN_HEIGHT / 16 };
            SDL_SetRenderDrawColor( gRenderer, 52, 61, 236, 0xFF ); 

            // SDL_SetTextInputRect(&fillRect);
       
            SDL_RenderFillRect( gRenderer, &vidyanchal );


             // Delhi - 16
            SDL_Rect fillRect6 = { SCREEN_WIDTH / 22 + 400, SCREEN_HEIGHT / 22+120, SCREEN_WIDTH / 10, SCREEN_HEIGHT / 16 };
            SDL_SetRenderDrawColor( gRenderer, 235, 52, 76, 0xFF ); 

            // SDL_SetTextInputRect(&fillRect);
       
            SDL_RenderFillRect( gRenderer, &fillRect6 );

            // Tennis Court

            SDL_Rect tennisCourt = { SCREEN_WIDTH / 22 + 200, SCREEN_HEIGHT / 22+200, SCREEN_WIDTH / 8, SCREEN_HEIGHT / 12 };
            SDL_SetRenderDrawColor( gRenderer,15, 77, 125, 0xFF ); 

            // SDL_SetTextInputRect(&fillRect);
       
            SDL_RenderFillRect( gRenderer, &tennisCourt );
            // Volley Ball Court
           	SDL_Rect volleyBallCourt = { SCREEN_WIDTH / 22 + 400, SCREEN_HEIGHT / 22+200, SCREEN_WIDTH / 8, SCREEN_HEIGHT / 12 };
            SDL_SetRenderDrawColor( gRenderer,92, 8, 8, 0xFF ); 

            // SDL_SetTextInputRect(&fillRect);
       
            SDL_RenderFillRect( gRenderer, &volleyBallCourt );

            // Shivalik

            SDL_Rect shivalik = { SCREEN_WIDTH / 22 + 375, SCREEN_HEIGHT / 22+300, SCREEN_WIDTH / 10, SCREEN_HEIGHT / 16 };
            SDL_SetRenderDrawColor( gRenderer,52, 61, 236, 0xFF  ); 

            // SDL_SetTextInputRect(&fillRect);
       
            SDL_RenderFillRect( gRenderer, &shivalik );

            // Zanskar

            SDL_Rect zanskar = { SCREEN_WIDTH / 22 + 200, SCREEN_HEIGHT / 22+300, SCREEN_WIDTH / 10, SCREEN_HEIGHT / 16 };
            SDL_SetRenderDrawColor( gRenderer,52, 61, 236, 0xFF  ); 

            // SDL_SetTextInputRect(&fillRect);
       
            SDL_RenderFillRect( gRenderer, &zanskar );            


            // SAC

            SDL_Rect sac = { SCREEN_WIDTH / 22, SCREEN_HEIGHT / 22+270, SCREEN_WIDTH / 16, SCREEN_HEIGHT / 10 };
            SDL_SetRenderDrawColor( gRenderer,164, 191, 31, 0xFF  ); 

            // SDL_SetTextInputRect(&fillRect);
       
            SDL_RenderFillRect( gRenderer, &sac );              


			// Masala Mix
	    SDL_Rect masalaMix = { SCREEN_WIDTH / 22+200,  SCREEN_HEIGHT / 22+310+SCREEN_HEIGHT / 16, SCREEN_WIDTH / 12, SCREEN_HEIGHT / 16 };
            SDL_SetRenderDrawColor( gRenderer, 46, 8, 15, 0xFF ); 

            SDL_RenderFillRect( gRenderer, &masalaMix );


            // Rajdhani
			SDL_Rect rajdhani = { SCREEN_WIDTH / 22+210+SCREEN_WIDTH / 12,SCREEN_HEIGHT / 22+310+SCREEN_HEIGHT / 16, SCREEN_WIDTH / 12, SCREEN_HEIGHT / 16 };
            SDL_SetRenderDrawColor( gRenderer, 19, 105, 191, 0xFF ); 

            SDL_RenderFillRect( gRenderer, &rajdhani );

            // Chaayos
			SDL_Rect chaayos = { SCREEN_WIDTH / 22+220+2*SCREEN_WIDTH / 12, SCREEN_HEIGHT / 22+310+SCREEN_HEIGHT / 16, SCREEN_WIDTH / 12, SCREEN_HEIGHT / 16 };
            SDL_SetRenderDrawColor( gRenderer, 22, 115, 39, 0xFF ); 

            SDL_RenderFillRect( gRenderer, &chaayos );

            // IIT-D Hospital
			SDL_Rect hospital = {  SCREEN_WIDTH / 22+200, SCREEN_HEIGHT / 22+410+SCREEN_HEIGHT / 16, SCREEN_WIDTH / 8, SCREEN_HEIGHT / 10 };
            SDL_SetRenderDrawColor( gRenderer, 255, 0, 0, 0xFF ); 

            SDL_RenderFillRect( gRenderer, &hospital );




            // Bharti - School of AI
			SDL_Rect bharti = {  SCREEN_WIDTH / 22+200 , SCREEN_HEIGHT / 22+430+SCREEN_HEIGHT / 16+  SCREEN_HEIGHT / 10, SCREEN_WIDTH / 8, SCREEN_HEIGHT / 10 };
            SDL_SetRenderDrawColor( gRenderer, 164, 191, 31, 0xFF ); 

            SDL_RenderFillRect( gRenderer, &bharti );

            // Large ground 

            SDL_Rect largeGround = {  SCREEN_WIDTH / 22 , SCREEN_HEIGHT / 22+450, SCREEN_WIDTH / 10, SCREEN_HEIGHT / 4 };
            SDL_SetRenderDrawColor( gRenderer, 92, 8, 8, 0xFF ); 

            SDL_RenderFillRect( gRenderer, &largeGround );

            // Staff canteen

            SDL_Rect staffCanteen = {  SCREEN_WIDTH / 22 , SCREEN_HEIGHT / 22+470 + SCREEN_HEIGHT / 4, SCREEN_WIDTH / 16, SCREEN_HEIGHT / 16 };
            SDL_SetRenderDrawColor( gRenderer, 4, 76, 201, 0xFF ); 

            SDL_RenderFillRect( gRenderer, &staffCanteen);            



            // LHC

            SDL_Rect LHC = {  SCREEN_WIDTH / 22 , SCREEN_HEIGHT / 22+490 + SCREEN_HEIGHT / 4 +  SCREEN_HEIGHT / 16, SCREEN_WIDTH / 12, SCREEN_HEIGHT / 12 };
            SDL_SetRenderDrawColor( gRenderer, 164, 191, 31, 0xFF ); 

            SDL_RenderFillRect( gRenderer, &LHC);            



            // Satpura

            SDL_Rect satpura ={ SCREEN_WIDTH / 22+230+3*SCREEN_WIDTH / 12, SCREEN_HEIGHT / 22+310+SCREEN_HEIGHT / 16+40, SCREEN_WIDTH / 10, SCREEN_HEIGHT / 16 };
            SDL_SetRenderDrawColor( gRenderer, 52, 61, 236, 0xFF ); 

            SDL_RenderFillRect( gRenderer, &satpura);  




            // Shiru's cafe

            SDL_Rect shiru ={ SCREEN_WIDTH / 22+220+2*SCREEN_WIDTH / 12, SCREEN_HEIGHT / 22+470 + SCREEN_HEIGHT / 4, SCREEN_WIDTH / 12, SCREEN_HEIGHT / 16 };
            SDL_SetRenderDrawColor( gRenderer, 171, 138, 29, 0xFF ); 

            SDL_RenderFillRect( gRenderer, &shiru);  

            // Amul
            SDL_Rect amul ={ SCREEN_WIDTH / 22+230+3*SCREEN_WIDTH / 12, SCREEN_HEIGHT / 22+470 + SCREEN_HEIGHT / 4, SCREEN_WIDTH / 12, SCREEN_HEIGHT / 16 };
            SDL_SetRenderDrawColor( gRenderer, 224, 4, 12, 0xFF ); 

            SDL_RenderFillRect( gRenderer, &amul);  

            // Nescafe
            SDL_Rect nescafe ={ SCREEN_WIDTH / 22+240+4*SCREEN_WIDTH / 12, SCREEN_HEIGHT / 22+470 + SCREEN_HEIGHT / 4, SCREEN_WIDTH / 12, SCREEN_HEIGHT / 16 };
            SDL_SetRenderDrawColor( gRenderer, 71, 0, 0, 0xFF ); 

            SDL_RenderFillRect( gRenderer, &nescafe);  


            // CCD 


            SDL_Rect ccd ={ SCREEN_WIDTH / 22+300+5*SCREEN_WIDTH / 12, SCREEN_HEIGHT / 22+440 + SCREEN_HEIGHT / 4, SCREEN_WIDTH / 12, SCREEN_HEIGHT / 16 };
            SDL_SetRenderDrawColor( gRenderer,224, 4, 12, 0xFF ); 

            SDL_RenderFillRect( gRenderer, &ccd); 

            // Dogra hall

            SDL_Rect dograHall ={ SCREEN_WIDTH / 22+300+5*SCREEN_WIDTH / 12, SCREEN_HEIGHT / 22+440 + SCREEN_HEIGHT / 4+ SCREEN_HEIGHT / 16+40, SCREEN_WIDTH / 12, SCREEN_HEIGHT / 16 };
            SDL_SetRenderDrawColor( gRenderer,164, 191, 31, 0xFF ); 

            SDL_RenderFillRect( gRenderer, &dograHall); 


            // Main building

            SDL_Rect mainBuilding ={  SCREEN_WIDTH / 22+220+2*SCREEN_WIDTH / 12, SCREEN_HEIGHT / 22+540 + SCREEN_HEIGHT / 4+ SCREEN_HEIGHT / 16+40, SCREEN_WIDTH / 4, SCREEN_HEIGHT / 12 };
            SDL_SetRenderDrawColor( gRenderer,164, 191, 31, 0xFF ); 

            SDL_RenderFillRect( gRenderer, &mainBuilding); 



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









            SDL_RenderPresent(gRenderer);                     

		}

	}



	return 0;
}

