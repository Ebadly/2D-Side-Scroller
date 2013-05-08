/*This source code copyrighted by Lazy Foo' Productions (2004-2013)
and may not be redistributed without written permission.*/

//The headers
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"
#include <string>
#include <sstream>

//Screen attributes
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int SCREEN_BPP = 32;

//The surfaces
SDL_Surface *background = NULL;
SDL_Surface *startStop = NULL;
SDL_Surface *seconds = NULL;
SDL_Surface *screen = NULL;

//The event structure
SDL_Event event;

//The font
TTF_Font *font = NULL;

//The color of the font
SDL_Color textColor = { 0xF0, 0xFF, 0xF0 };

SDL_Surface *load_image( std::string filename ) {
    SDL_Surface *loadedImage = NULL;
    SDL_Surface *optimizedImage = NULL;
    loadedImage = IMG_Load( filename.c_str() );
    if ( loadedImage != NULL ) {
        optimizedImage = SDL_DisplayFormat( loadedImage );
        SDL_FreeSurface( loadedImage );
        if ( optimizedImage != NULL ) {
            SDL_SetColorKey( optimizedImage, SDL_SRCCOLORKEY, SDL_MapRGB( optimizedImage->format, 0, 0xFF, 0xFF ) );
        }
    }
    return optimizedImage;
}

void apply_surface( int x, int y, SDL_Surface *source, SDL_Surface *destination, SDL_Rect *clip = NULL ) {
    SDL_Rect offset;
    offset.x = x;
    offset.y = y;

    SDL_BlitSurface( source, clip, destination, &offset );
}

bool init() {
    if ( SDL_Init( SDL_INIT_EVERYTHING ) == -1) {
        return false;
    }

    screen = SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE );
    if ( screen == NULL ) {
        return false;
    }
    if ( TTF_Init() == -1 ) {
        return false;
    }
    SDL_WM_SetCaption( "Timer Test", NULL );
    return true;
}

bool load_files() {
    background = load_image( "background.png" );
    font = TTF_OpenFont( "lazy.ttf", 36 );
    if ( background == NULL ) {
        return false;
    }

    if ( font == NULL ) {
        return false;
    }

    return true;
}

void clean_up() {
    SDL_FreeSurface( background );
    SDL_FreeSurface( startStop );

    TTF_CloseFont( font );
    TTF_Quit();
    SDL_Quit();
}

int main( int argc, char* args[] ) {
    bool quit = false;
    //The timer starting time
    Uint32 start = 0;

    //The timer start/stop flag
    bool running = true;

    if ( init() == false ) {
        return 1;
    }

    if ( load_files() == false ) {
        return 1;
    }

    startStop = TTF_RenderText_Solid( font, "Press S to start or stop the timer", textColor );

    //Start the timer
    start = SDL_GetTicks();

    //While the user hasn't quit 
    while ( quit == false ) {
        while ( SDL_PollEvent( &event ) ) {
            if ( event.type == SDL_KEYDOWN ) {
                if ( event.key.keysym.sym == SDLK_s ) {
                    //If the timer is running
                    if ( running == true ) {
                        //Stop the timer 
                        running = false;
                        start = 0;
                    } else {
                        //Start the timer 
                        running = true;
                        start = SDL_GetTicks();
                    }
                }
            } else if( event.type == SDL_QUIT ) {
                //Quit
                quit = true;
            }
        }
        apply_surface( 0, 0, background, screen );

        apply_surface( ( SCREEN_WIDTH - startStop->w ) / 2, 200, startStop, screen );

        if ( running == true ) {
            std::stringstream time;
            time << "Timer: " << SDL_GetTicks() - start;
            seconds = TTF_RenderText_Solid( font, time.str().c_str(), textColor );
            apply_surface( ( SCREEN_WIDTH - seconds->w ) / 2, 50, seconds, screen );
            SDL_FreeSurface( seconds );
        }

        if ( SDL_Flip( screen ) == -1 ) {
            return 1;
        }
    }

    clean_up();
}
