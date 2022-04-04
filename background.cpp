#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <SDL2_ttf/SDL_ttf.h>

#include <stdio.h>
#include <string>


const int SCREEN_WIDTH = 1520;
const int SCREEN_HEIGHT = 1020;

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The window renderer
SDL_Renderer* gRenderer = NULL;

//Current displayed texture
SDL_Texture* gTexture = NULL;

TTF_Font* font;

void disptext(SDL_Renderer* gRenderer, int x, int y, int w, int h, char* s){
    //writing text in the box


    TTF_Init();
                //this opens a font style and sets a size
    
    TTF_Font* Sans = TTF_OpenFont("/Library/Fonts/Arial Unicode.ttf", 24);          //CHANGE THE FONT PATH TO AN APPROPRIATE ONE ACCORDING TO YOUR SYSTEM

    // this is the color in rgb format,
    // maxing out all would give you the color white,
    // and it will be your text's color
    SDL_Color White = {255, 255, 255};

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
                TTF_CloseFont(font);
                TTF_Quit();


}


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

           
//writing text in the box

            disptext(gRenderer, SCREEN_WIDTH / 22, SCREEN_HEIGHT / 22, SCREEN_WIDTH / 10, SCREEN_HEIGHT / 16, "Nilgiri") ;

			// Karakoram       

			SDL_Rect karakoram = { SCREEN_WIDTH / 22 + 200, SCREEN_HEIGHT / 22,SCREEN_WIDTH / 10, SCREEN_HEIGHT / 16 };
            SDL_SetRenderDrawColor( gRenderer, 52, 61, 236, 0xFF ); 
            
            // SDL_SetTextInputRect(&fillRect);
       
            SDL_RenderFillRect( gRenderer, &karakoram );			
            
            
            disptext(gRenderer, SCREEN_WIDTH / 22 + 200, SCREEN_HEIGHT / 22, SCREEN_WIDTH / 10, SCREEN_HEIGHT / 16, "Karakoram" ) ;
            
            
            
            
            // Aravali
			SDL_Rect aravali = { SCREEN_WIDTH / 22 + 400, SCREEN_HEIGHT / 22, SCREEN_WIDTH / 10, SCREEN_HEIGHT / 16 };
            SDL_SetRenderDrawColor( gRenderer, 52, 61, 236, 0xFF ); 

            // SDL_SetTextInputRect(&fillRect);
       
            SDL_RenderFillRect( gRenderer, &aravali);
            
            
            disptext(gRenderer, SCREEN_WIDTH / 22 + 400, SCREEN_HEIGHT / 22, SCREEN_WIDTH / 10, SCREEN_HEIGHT / 16, "Aravali" ) ;
            

            // Jwala
			SDL_Rect jwala = { SCREEN_WIDTH / 22 + 800, SCREEN_HEIGHT / 22, SCREEN_WIDTH / 10, SCREEN_HEIGHT / 16 };
            SDL_SetRenderDrawColor( gRenderer, 52, 61, 236, 0xFF ); 

            // SDL_SetTextInputRect(&fillRect);
       
            SDL_RenderFillRect( gRenderer, &jwala );
            
            
            disptext(gRenderer, SCREEN_WIDTH / 22 + 800, SCREEN_HEIGHT / 22, SCREEN_WIDTH / 10, SCREEN_HEIGHT / 16, "Jwala" ) ;

            // Kumaon
            SDL_Rect kumaon = { SCREEN_WIDTH / 22 + 800, SCREEN_HEIGHT / 22+100, SCREEN_WIDTH / 10, SCREEN_HEIGHT / 16 };
            SDL_SetRenderDrawColor( gRenderer, 52, 61, 236, 0xFF ); 

            // SDL_SetTextInputRect(&fillRect);
       
            SDL_RenderFillRect( gRenderer, &kumaon );

            disptext(gRenderer, SCREEN_WIDTH / 22 + 800, SCREEN_HEIGHT / 22 + 100, SCREEN_WIDTH / 10, SCREEN_HEIGHT / 16, "Kumaon" ) ;
            
            
            // Vidyanchal
            SDL_Rect vidyanchal = { SCREEN_WIDTH / 22 + 800, SCREEN_HEIGHT / 22+250, SCREEN_WIDTH / 10, SCREEN_HEIGHT / 16 };
            SDL_SetRenderDrawColor( gRenderer, 52, 61, 236, 0xFF );

            // SDL_SetTextInputRect(&fillRect);
       
            SDL_RenderFillRect( gRenderer, &vidyanchal );


            disptext(gRenderer, SCREEN_WIDTH / 22 + 800, SCREEN_HEIGHT / 22 + 250, SCREEN_WIDTH / 10, SCREEN_HEIGHT / 16, "Vidyanchal" ) ;
            
             // Delhi - 16
            SDL_Rect fillRect6 = { SCREEN_WIDTH / 22 + 400, SCREEN_HEIGHT / 22+120, SCREEN_WIDTH / 10, SCREEN_HEIGHT / 16 };
            SDL_SetRenderDrawColor( gRenderer, 235, 52, 76, 0xFF ); 

            // SDL_SetTextInputRect(&fillRect);
       
            SDL_RenderFillRect( gRenderer, &fillRect6 );
            
            
            disptext(gRenderer, SCREEN_WIDTH / 22 + 400, SCREEN_HEIGHT / 22 + 120, SCREEN_WIDTH / 10, SCREEN_HEIGHT / 16, "Dilli-16" ) ;

            // Tennis Court

            SDL_Rect tennisCourt = { SCREEN_WIDTH / 22 + 200, SCREEN_HEIGHT / 22+200, SCREEN_WIDTH / 8, SCREEN_HEIGHT / 12 };
            SDL_SetRenderDrawColor( gRenderer,15, 77, 125, 0xFF ); 

            // SDL_SetTextInputRect(&fillRect);
       
            SDL_RenderFillRect( gRenderer, &tennisCourt );
            
            
            
            disptext(gRenderer, SCREEN_WIDTH / 22 + 200, SCREEN_HEIGHT / 22+200, SCREEN_WIDTH / 8, SCREEN_HEIGHT / 12, "Tennis Court" ) ;
            
            
            // Volley Ball Court
           	SDL_Rect volleyBallCourt = { SCREEN_WIDTH / 22 + 400, SCREEN_HEIGHT / 22+200, SCREEN_WIDTH / 8, SCREEN_HEIGHT / 12 };
            SDL_SetRenderDrawColor( gRenderer,92, 8, 8, 0xFF ); 

            // SDL_SetTextInputRect(&fillRect);
       
            SDL_RenderFillRect( gRenderer, &volleyBallCourt );
            
            
            
            disptext(gRenderer, SCREEN_WIDTH / 22 + 400, SCREEN_HEIGHT / 22+200, SCREEN_WIDTH / 8, SCREEN_HEIGHT / 12, "Volleyball Court" ) ;
            
            
            

            // Shivalik

            SDL_Rect shivalik = { SCREEN_WIDTH / 22 + 375, SCREEN_HEIGHT / 22+300, SCREEN_WIDTH / 10, SCREEN_HEIGHT / 16 };
            SDL_SetRenderDrawColor( gRenderer,52, 61, 236, 0xFF  ); 

            // SDL_SetTextInputRect(&fillRect);
       
            SDL_RenderFillRect( gRenderer, &shivalik );
            
            
            disptext(gRenderer, SCREEN_WIDTH / 22 + 375, SCREEN_HEIGHT / 22+300, SCREEN_WIDTH / 10, SCREEN_HEIGHT / 16, "Shivalik" ) ;
            
            

            // Zanskar

            SDL_Rect zanskar = { SCREEN_WIDTH / 22 + 200, SCREEN_HEIGHT / 22+300, SCREEN_WIDTH / 10, SCREEN_HEIGHT / 16 };
            SDL_SetRenderDrawColor( gRenderer,52, 61, 236, 0xFF  ); 

            // SDL_SetTextInputRect(&fillRect);
       
            SDL_RenderFillRect( gRenderer, &zanskar );            

            
            disptext(gRenderer, SCREEN_WIDTH / 22 + 200, SCREEN_HEIGHT / 22+300, SCREEN_WIDTH / 10, SCREEN_HEIGHT / 16, "Zanskar" ) ;
            

            // SAC

            SDL_Rect sac = { SCREEN_WIDTH / 22, SCREEN_HEIGHT / 22+270, SCREEN_WIDTH / 16, SCREEN_HEIGHT / 10 };
            SDL_SetRenderDrawColor( gRenderer,164, 191, 31, 0xFF  ); 

            // SDL_SetTextInputRect(&fillRect);
       
            SDL_RenderFillRect( gRenderer, &sac );
            
            
            
            disptext(gRenderer, SCREEN_WIDTH / 22, SCREEN_HEIGHT / 22+270, SCREEN_WIDTH / 16, SCREEN_HEIGHT / 10, "SAC" ) ;



			// Masala Mix
	    SDL_Rect masalaMix = { SCREEN_WIDTH / 22+200,  SCREEN_HEIGHT / 22+310+SCREEN_HEIGHT / 16, SCREEN_WIDTH / 12, SCREEN_HEIGHT / 16 };
            SDL_SetRenderDrawColor( gRenderer, 46, 8, 15, 0xFF ); 

            SDL_RenderFillRect( gRenderer, &masalaMix );
            
            
            
            disptext(gRenderer,  SCREEN_WIDTH / 22+200,  SCREEN_HEIGHT / 22+310+SCREEN_HEIGHT / 16, SCREEN_WIDTH / 12, SCREEN_HEIGHT / 16, "Masala Mix" ) ;



            // Rajdhani
			SDL_Rect rajdhani = { SCREEN_WIDTH / 22+210+SCREEN_WIDTH / 12,SCREEN_HEIGHT / 22+310+SCREEN_HEIGHT / 16, SCREEN_WIDTH / 12, SCREEN_HEIGHT / 16 };
            SDL_SetRenderDrawColor( gRenderer, 19, 105, 191, 0xFF ); 

            SDL_RenderFillRect( gRenderer, &rajdhani );
            
            
            disptext(gRenderer,  SCREEN_WIDTH / 22+210+SCREEN_WIDTH / 12,SCREEN_HEIGHT / 22+310+SCREEN_HEIGHT / 16, SCREEN_WIDTH / 12, SCREEN_HEIGHT / 16 , "Rajdhani" ) ;
            
            

            // Chaayos
			SDL_Rect chaayos = { SCREEN_WIDTH / 22+220+2*SCREEN_WIDTH / 12, SCREEN_HEIGHT / 22+310+SCREEN_HEIGHT / 16, SCREEN_WIDTH / 12, SCREEN_HEIGHT / 16 };
            SDL_SetRenderDrawColor( gRenderer, 22, 115, 39, 0xFF ); 

            SDL_RenderFillRect( gRenderer, &chaayos );
            
            
            disptext(gRenderer,  SCREEN_WIDTH / 22+220+2*SCREEN_WIDTH / 12, SCREEN_HEIGHT / 22+310+SCREEN_HEIGHT / 16, SCREEN_WIDTH / 12, SCREEN_HEIGHT / 16, "Chaayos" ) ;
            
            

            // IIT-D Hospital
			SDL_Rect hospital = {  SCREEN_WIDTH / 22+200, SCREEN_HEIGHT / 22+410+SCREEN_HEIGHT / 16, SCREEN_WIDTH / 8, SCREEN_HEIGHT / 10 };
            SDL_SetRenderDrawColor( gRenderer, 255, 0, 0, 0xFF ); 

            SDL_RenderFillRect( gRenderer, &hospital );

                
            disptext(gRenderer,  SCREEN_WIDTH / 22+200, SCREEN_HEIGHT / 22+410+SCREEN_HEIGHT / 16, SCREEN_WIDTH / 8, SCREEN_HEIGHT / 10, "Hospital" ) ;


            // Bharti - School of AI
			SDL_Rect bharti = {  SCREEN_WIDTH / 22+200 , SCREEN_HEIGHT / 22+430+SCREEN_HEIGHT / 16+  SCREEN_HEIGHT / 10, SCREEN_WIDTH / 8, SCREEN_HEIGHT / 10 };
            SDL_SetRenderDrawColor( gRenderer, 164, 191, 31, 0xFF ); 

            SDL_RenderFillRect( gRenderer, &bharti );
            
            disptext(gRenderer,  SCREEN_WIDTH / 22+200 , SCREEN_HEIGHT / 22+430+SCREEN_HEIGHT / 16+  SCREEN_HEIGHT / 10, SCREEN_WIDTH / 8, SCREEN_HEIGHT / 10 , "Bharti Building" ) ;

            // Large ground 

            SDL_Rect largeGround = {  SCREEN_WIDTH / 22 , SCREEN_HEIGHT / 22+450, SCREEN_WIDTH / 10, SCREEN_HEIGHT / 4 };
            SDL_SetRenderDrawColor( gRenderer, 92, 8, 8, 0xFF ); 

            SDL_RenderFillRect( gRenderer, &largeGround );
            
            
            
            disptext(gRenderer,  SCREEN_WIDTH / 22 , SCREEN_HEIGHT / 22+450, SCREEN_WIDTH / 10, SCREEN_HEIGHT / 4 , "Large Ground" ) ;

            // Staff canteen

            SDL_Rect staffCanteen = {  SCREEN_WIDTH / 22 , SCREEN_HEIGHT / 22+470 + SCREEN_HEIGHT / 4, SCREEN_WIDTH / 16, SCREEN_HEIGHT / 16 };
            SDL_SetRenderDrawColor( gRenderer, 4, 76, 201, 0xFF ); 

            SDL_RenderFillRect( gRenderer, &staffCanteen);            

            
            
            disptext(gRenderer,  SCREEN_WIDTH / 22 , SCREEN_HEIGHT / 22+470 + SCREEN_HEIGHT / 4, SCREEN_WIDTH / 16, SCREEN_HEIGHT / 16  , "Staff Canteen" ) ;


            // LHC

            SDL_Rect LHC = {  SCREEN_WIDTH / 22 , SCREEN_HEIGHT / 22+490 + SCREEN_HEIGHT / 4 +  SCREEN_HEIGHT / 16, SCREEN_WIDTH / 12, SCREEN_HEIGHT / 12 };
            SDL_SetRenderDrawColor( gRenderer, 164, 191, 31, 0xFF ); 

            SDL_RenderFillRect( gRenderer, &LHC);
            
            
            
            disptext(gRenderer,  SCREEN_WIDTH / 22 , SCREEN_HEIGHT / 22+490 + SCREEN_HEIGHT / 4 +  SCREEN_HEIGHT / 16, SCREEN_WIDTH / 12, SCREEN_HEIGHT / 12  , "LHC" ) ;



            // Satpura

            SDL_Rect satpura ={ SCREEN_WIDTH / 22+230+3*SCREEN_WIDTH / 12, SCREEN_HEIGHT / 22+310+SCREEN_HEIGHT / 16+40, SCREEN_WIDTH / 10, SCREEN_HEIGHT / 16 };
            SDL_SetRenderDrawColor( gRenderer, 52, 61, 236, 0xFF ); 

            SDL_RenderFillRect( gRenderer, &satpura);  


            
            
            disptext(gRenderer,  SCREEN_WIDTH / 22+230+3*SCREEN_WIDTH / 12, SCREEN_HEIGHT / 22+310+SCREEN_HEIGHT / 16+40, SCREEN_WIDTH / 10, SCREEN_HEIGHT / 16  , "Satpura" ) ;



            // Shiru's cafe

            SDL_Rect shiru ={ SCREEN_WIDTH / 22+220+2*SCREEN_WIDTH / 12, SCREEN_HEIGHT / 22+470 + SCREEN_HEIGHT / 4, SCREEN_WIDTH / 12, SCREEN_HEIGHT / 16 };
            SDL_SetRenderDrawColor( gRenderer, 171, 138, 29, 0xFF ); 

            SDL_RenderFillRect( gRenderer, &shiru);
            
            
            
            disptext(gRenderer,  SCREEN_WIDTH / 22+220+2*SCREEN_WIDTH / 12, SCREEN_HEIGHT / 22+470 + SCREEN_HEIGHT / 4, SCREEN_WIDTH / 12, SCREEN_HEIGHT / 16  , "Shiru's Cafe" ) ;
            
            

            // Amul
            SDL_Rect amul ={ SCREEN_WIDTH / 22+230+3*SCREEN_WIDTH / 12, SCREEN_HEIGHT / 22+470 + SCREEN_HEIGHT / 4, SCREEN_WIDTH / 12, SCREEN_HEIGHT / 16 };
            SDL_SetRenderDrawColor( gRenderer, 224, 4, 12, 0xFF ); 

            SDL_RenderFillRect( gRenderer, &amul);
            
            
            
            
            disptext(gRenderer,   SCREEN_WIDTH / 22+230+3*SCREEN_WIDTH / 12, SCREEN_HEIGHT / 22+470 + SCREEN_HEIGHT / 4, SCREEN_WIDTH / 12, SCREEN_HEIGHT / 16 , "Amul" ) ;

            // Nescafe
            SDL_Rect nescafe ={ SCREEN_WIDTH / 22+240+4*SCREEN_WIDTH / 12, SCREEN_HEIGHT / 22+470 + SCREEN_HEIGHT / 4, SCREEN_WIDTH / 12, SCREEN_HEIGHT / 16 };
            SDL_SetRenderDrawColor( gRenderer, 71, 0, 0, 0xFF ); 

            SDL_RenderFillRect( gRenderer, &nescafe);
            
            disptext(gRenderer,   SCREEN_WIDTH / 22+240+4*SCREEN_WIDTH / 12, SCREEN_HEIGHT / 22+470 + SCREEN_HEIGHT / 4, SCREEN_WIDTH / 12, SCREEN_HEIGHT / 16 , "Nescafe" ) ;


            // CCD 


            SDL_Rect ccd ={ SCREEN_WIDTH / 22+300+5*SCREEN_WIDTH / 12, SCREEN_HEIGHT / 22+440 + SCREEN_HEIGHT / 4, SCREEN_WIDTH / 12, SCREEN_HEIGHT / 16 };
            SDL_SetRenderDrawColor( gRenderer,224, 4, 12, 0xFF ); 

            SDL_RenderFillRect( gRenderer, &ccd);
            
            
            
            
            disptext(gRenderer,   SCREEN_WIDTH / 22+300+5*SCREEN_WIDTH / 12, SCREEN_HEIGHT / 22+440 + SCREEN_HEIGHT / 4, SCREEN_WIDTH / 12, SCREEN_HEIGHT / 16 , "Cafe Coffee Day" ) ;

            // Dogra hall

            SDL_Rect dograHall ={ SCREEN_WIDTH / 22+300+5*SCREEN_WIDTH / 12, SCREEN_HEIGHT / 22+440 + SCREEN_HEIGHT / 4+ SCREEN_HEIGHT / 16+40, SCREEN_WIDTH / 12, SCREEN_HEIGHT / 16 };
            SDL_SetRenderDrawColor( gRenderer,164, 191, 31, 0xFF ); 

            SDL_RenderFillRect( gRenderer, &dograHall);
            
            
            
            disptext(gRenderer,   SCREEN_WIDTH / 22+300+5*SCREEN_WIDTH / 12, SCREEN_HEIGHT / 22+440 + SCREEN_HEIGHT / 4+ SCREEN_HEIGHT / 16+40, SCREEN_WIDTH / 12, SCREEN_HEIGHT / 16, "Dogra Hall" ) ;
            
            


            // Main building

            SDL_Rect mainBuilding ={  SCREEN_WIDTH / 22+220+2*SCREEN_WIDTH / 12, SCREEN_HEIGHT / 22+540 + SCREEN_HEIGHT / 4+ SCREEN_HEIGHT / 16+40, SCREEN_WIDTH / 4, SCREEN_HEIGHT / 12 };
            SDL_SetRenderDrawColor( gRenderer,164, 191, 31, 0xFF ); 

            SDL_RenderFillRect( gRenderer, &mainBuilding); 


            
            disptext(gRenderer,  SCREEN_WIDTH / 22+220+2*SCREEN_WIDTH / 12, SCREEN_HEIGHT / 22+540 + SCREEN_HEIGHT / 4+ SCREEN_HEIGHT / 16+40, SCREEN_WIDTH / 4, SCREEN_HEIGHT / 12 , "Main Building" ) ;



            SDL_RenderPresent(gRenderer);                     

		}

	}



	return 0;
}
