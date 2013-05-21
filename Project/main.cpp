#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"
#include "ImageManager.h"
#include "SoundManager.h"
#include <string>

//The attributes of the screen
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int SCREEN_BPP = 32;

//The surfaces that will be used
SDL_Surface *message = NULL;
SDL_Surface *splash = NULL;
SDL_Surface *background = NULL;
SDL_Surface *screen = NULL;

//The event structure
SDL_Event event;

//Music structure
Mix_Music *music = NULL;

//Managers
ImageManager *imageManager;
SoundManager *soundManager;


SDL_Surface * load_image( std::string filename );

bool init_sdl();
void clean_up();

int main( int argc, char* args[] ) {
    bool quit = false;
    imageManager = new ImageManager;
    soundManager = new SoundManager;

    //Kill the program if it didn't init successfully.
    if( !init_sdl() ) {
        return -1;
    }

    // Load the images 
    splash = load_image( "background.jpg" );
    message = load_image( "hello.bmp" );
    background = load_image( "background.bmp" );

    imageManager->draw_to_surface( background, screen );


    // TODO: REMOVE TEMPORARY COUNTER AND REPLACE WITH A TIMER 
    int TEMPORARYCOUNTER = 0;
    while( quit == false ) {
        while( SDL_PollEvent( &event ) ) {
            if( event.type == SDL_QUIT ) {
                quit = true;
            }

            if( Mix_PlayingMusic() == 0 ) {
                //Play the music
                soundManager->play_music( "titlemusic.wav" );
            }
        }

        if ( SDL_Flip( screen ) == -1 ) {
            return 1;
        }

        TEMPORARYCOUNTER++;
        if(TEMPORARYCOUNTER == 500) {
            imageManager->draw_to_surface( splash, screen );
        }
    }

    // Apply the message to the screen
    //apply_surface( 180, 140, message, screen );

    clean_up();
    return 0;
}


bool init_sdl() {
    if ( SDL_Init( SDL_INIT_EVERYTHING ) == -1 ) {
        return false;
    }
    screen = SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE );
    if ( screen == NULL ) {
        return false;
    }
    // Set the window caption
    SDL_WM_SetCaption( "Hello World", NULL );
    return true;
}

SDL_Surface *load_image( std::string filename ) {
    //The image that's loaded
    SDL_Surface* loadedImage = NULL;

    //The optimized image that will be used
    SDL_Surface* optimizedImage = NULL;

    //Load the image using SDL_image
    loadedImage = IMG_Load( filename.c_str() );

    //If the image loaded
    if( loadedImage != NULL ) {
        //Create an optimized image
        optimizedImage = SDL_DisplayFormat( loadedImage );
        
        //Free the old image
        SDL_FreeSurface( loadedImage );
    }

    //Return the optimized image
    return optimizedImage;
}

void clean_up() {
    delete imageManager;
    delete soundManager;
    // Free the surfaces 
    SDL_FreeSurface( message );
    SDL_FreeSurface( background );
    SDL_FreeSurface( splash );
    // Quit SDL 
    SDL_Quit();
}
