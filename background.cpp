#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include <stdio.h>
#include <string>


const int SCREEN_WIDTH = 1020;
const int SCREEN_HEIGHT = 980;

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The window renderer
SDL_Renderer* gRenderer = NULL;

//Current displayed texture
SDL_Texture* gTexture = NULL;


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
		bool quit = false;

		SDL_Event e;

		while(!quit){

			while(SDL_PollEvent(&e)!=0){
				if(e.type == SDL_QUIT){
					quit = true;
				}

			}
			SDL_SetRenderDrawColor(gRenderer,0x00,0x00,0x00,0x00);
			SDL_RenderClear(gRenderer);
			
			// Nilgiri
			SDL_Rect fillRect = { SCREEN_WIDTH / 22, SCREEN_HEIGHT / 22, SCREEN_WIDTH / 10, SCREEN_HEIGHT / 16 };
            SDL_SetRenderDrawColor( gRenderer, 52, 61, 236, 0xFF ); 

            SDL_RenderFillRect( gRenderer, &fillRect );
			// SDL_RenderCopy(gRenderer,gTexture, NULL, NULL);

			// Karakoram       

			SDL_Rect fillRect2 = { SCREEN_WIDTH / 22 + 200, SCREEN_HEIGHT / 22, SCREEN_WIDTH / 10, SCREEN_HEIGHT / 16 };
            SDL_SetRenderDrawColor( gRenderer, 52, 61, 236, 0xFF ); 

            // SDL_SetTextInputRect(&fillRect);
       
            SDL_RenderFillRect( gRenderer, &fillRect2 );			

            // Aravali
			SDL_Rect fillRect3 = { SCREEN_WIDTH / 22 + 400, SCREEN_HEIGHT / 22, SCREEN_WIDTH / 10, SCREEN_HEIGHT / 16 };
            SDL_SetRenderDrawColor( gRenderer, 52, 61, 236, 0xFF ); 

            // SDL_SetTextInputRect(&fillRect);
       
            SDL_RenderFillRect( gRenderer, &fillRect3 );	

            // Jwala
			SDL_Rect fillRect4 = { SCREEN_WIDTH / 22 + 800, SCREEN_HEIGHT / 22, SCREEN_WIDTH / 10, SCREEN_HEIGHT / 16 };
            SDL_SetRenderDrawColor( gRenderer, 52, 61, 236, 0xFF ); 

            // SDL_SetTextInputRect(&fillRect);
       
            SDL_RenderFillRect( gRenderer, &fillRect4 );	

            // Kumaon
            SDL_Rect fillRect5 = { SCREEN_WIDTH / 22 + 800, SCREEN_HEIGHT / 22+100, SCREEN_WIDTH / 10, SCREEN_HEIGHT / 16 };
            SDL_SetRenderDrawColor( gRenderer, 52, 61, 236, 0xFF ); 

            // SDL_SetTextInputRect(&fillRect);
       
            SDL_RenderFillRect( gRenderer, &fillRect5 );


             // Delhi - 16
            SDL_Rect fillRect6 = { SCREEN_WIDTH / 22 + 400, SCREEN_HEIGHT / 22+120, SCREEN_WIDTH / 10, SCREEN_HEIGHT / 16 };
            SDL_SetRenderDrawColor( gRenderer, 235, 52, 76, 0xFF ); 

            // SDL_SetTextInputRect(&fillRect);
       
            SDL_RenderFillRect( gRenderer, &fillRect6 );

            // Tennis Court

            SDL_Rect tennisCourt = { SCREEN_WIDTH / 22 + 200, SCREEN_HEIGHT / 22+200, SCREEN_WIDTH / 8, SCREEN_HEIGHT / 6 };
            SDL_SetRenderDrawColor( gRenderer,15, 77, 125, 0xFF ); 

            // SDL_SetTextInputRect(&fillRect);
       
            SDL_RenderFillRect( gRenderer, &tennisCourt );
            // Volley Ball Court
           	SDL_Rect volleyBallCourt = { SCREEN_WIDTH / 22 + 375, SCREEN_HEIGHT / 22+200, SCREEN_WIDTH / 8, SCREEN_HEIGHT / 6 };
            SDL_SetRenderDrawColor( gRenderer,92, 8, 8, 0xFF ); 

            // SDL_SetTextInputRect(&fillRect);
       
            SDL_RenderFillRect( gRenderer, &volleyBallCourt );

            // Shivalik

            SDL_Rect shivalik = { SCREEN_WIDTH / 22 + 350, SCREEN_HEIGHT / 22+400, SCREEN_WIDTH / 10, SCREEN_HEIGHT / 16 };
            SDL_SetRenderDrawColor( gRenderer,52, 61, 236, 0xFF  ); 

            // SDL_SetTextInputRect(&fillRect);
       
            SDL_RenderFillRect( gRenderer, &shivalik );

            // Zanskar

            SDL_Rect zanskar = { SCREEN_WIDTH / 22 + 200, SCREEN_HEIGHT / 22+400, SCREEN_WIDTH / 10, SCREEN_HEIGHT / 16 };
            SDL_SetRenderDrawColor( gRenderer,52, 61, 236, 0xFF  ); 

            // SDL_SetTextInputRect(&fillRect);
       
            SDL_RenderFillRect( gRenderer, &zanskar );            


            // SAC

            SDL_Rect sac = { SCREEN_WIDTH / 22, SCREEN_HEIGHT / 22+400, SCREEN_WIDTH / 16, SCREEN_HEIGHT / 10 };
            SDL_SetRenderDrawColor( gRenderer,164, 191, 31, 0xFF  ); 

            // SDL_SetTextInputRect(&fillRect);
       
            SDL_RenderFillRect( gRenderer, &sac );              


			// Masala Mix
			SDL_Rect masalaMix = { SCREEN_WIDTH / 22+200, SCREEN_HEIGHT / 22+410+SCREEN_HEIGHT / 16, SCREEN_WIDTH / 12, SCREEN_HEIGHT / 16 };
            SDL_SetRenderDrawColor( gRenderer, 46, 8, 15, 0xFF ); 

            SDL_RenderFillRect( gRenderer, &masalaMix );


            // Rajdhani
			SDL_Rect rajdhani = { SCREEN_WIDTH / 22+210+SCREEN_WIDTH / 12, SCREEN_HEIGHT / 22+410+SCREEN_HEIGHT / 16, SCREEN_WIDTH / 12, SCREEN_HEIGHT / 16 };
            SDL_SetRenderDrawColor( gRenderer, 19, 105, 191, 0xFF ); 

            SDL_RenderFillRect( gRenderer, &rajdhani );

            // Chaayos
			SDL_Rect chaayos = { SCREEN_WIDTH / 22+220+2*SCREEN_WIDTH / 12, SCREEN_HEIGHT / 22+410+SCREEN_HEIGHT / 16, SCREEN_WIDTH / 12, SCREEN_HEIGHT / 16 };
            SDL_SetRenderDrawColor( gRenderer, 22, 115, 39, 0xFF ); 

            SDL_RenderFillRect( gRenderer, &chaayos );

            // IIT-D Hospital


            SDL_RenderPresent(gRenderer);




		}

	}



	return 0;
}

