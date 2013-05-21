#include <iostream>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include <string>

#include "../SoundManager/SoundManager.h"
#include "../ScreenManager/ScreenManager.h"


//Screen attributes
const int SCREEN_HEIGHT = 480;
const int SCREEN_BPP = 32;
const int SCREEN_WIDTH = 640;

//The frame rate
const int FRAMES_PER_SECOND = 20;

//The surfaces
SDL_Surface *screen = NULL;
SDL_Surface *startScreen = NULL;
SDL_Surface *gameScreen = NULL;

//The event structure
SDL_Event event;

//Some booleans for game state
bool gameStart = false;

//Main functions
bool init();
bool load_files();
void clean_up();

//Event handling functions
void handle_return_key();

int main( int argc, char *args[] ) {
    bool quit = false;
    ScreenManager *screenManager = new ScreenManager();
    SoundManager *soundManager = new SoundManager();


    if ( init() == false ) {
        return 1;
    }

    if ( load_files() == false ) {
        return 1;
    }

    while ( quit == false ) {
        while ( SDL_PollEvent( &event ) ) {

            if ( event.type == SDL_KEYDOWN ) {
                switch ( event.key.keysym.sym ) {
                    case SDLK_RETURN:
                        handle_return_key();
                        break;
                    default:
                        ;
                }
            }

            if ( event.type == SDL_QUIT ) {
                quit = true;
            }
        }


        startScreen = screenManager->load_image( "../ScreenManager/Images/test.png" );

        if ( soundManager->play_music( "../beat.wav" ) ) {
            return 1;
        }

        screenManager->apply_surface( 0, 0, startScreen, screen);


        if ( gameStart ) {
            //apply the gameScreen surface
        } else {
            //apply the startScreen surface
        }

        //Update the screen
        if ( SDL_Flip( screen ) == -1 ) {
            return 1;
        }
    }

    clean_up();
    return 0;
}

bool init() {
    if ( SDL_Init( SDL_INIT_EVERYTHING ) == -1 ) {
        return false;
    }

    //Set up the screen
    screen = SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE );

    if ( screen == NULL ) {
        return false;
    }

    //Set the window caption
    SDL_WM_SetCaption( "Game", NULL );

    return true;

}

bool load_files() {
    return true;
}

void clean_up() {
    SDL_FreeSurface( startScreen );
    SDL_FreeSurface( gameScreen );
    SDL_FreeSurface( screen );
    SDL_Quit();
}

void handle_return_key() {
    if ( startScreen ) {
        //clear it
        SDL_FreeSurface( startScreen );
        gameStart = true;
    } else {
        //at game screen
    }
}
