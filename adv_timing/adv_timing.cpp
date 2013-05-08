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
SDL_Surface *pauseMessage = NULL;
SDL_Surface *seconds = NULL;
SDL_Surface *screen = NULL;

//The event structure
SDL_Event event;

//The font
TTF_Font *font = NULL;

//The color of the font
SDL_Color textColor = { 0, 0, 0 };

class Timer 
{
public:
    //Initialize variables
    Timer();
    //The various clock actions
    void start();
    void stop();
    void pause();
    void unpause();
    //Gets the timer's time
    int get_ticks();
    //Check the status of the timer
    bool is_started();
    bool is_paused();

private:
    //The clock time when the timer started
    int startTicks;
    //The ticks stored when the timer was paused
    int pausedTicks;
    //The timer status
    bool paused;
    bool started;
};

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
    if ( SDL_Init( SDL_INIT_EVERYTHING ) == -1 ) {
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
    //Load the background image
    background = load_image( "background.png" );
    font = TTF_OpenFont( "lazy.ttf", 24 );
    //If there was a problem in loading the background
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
    SDL_FreeSurface( pauseMessage );
    TTF_CloseFont( font );
    TTF_Quit();
    SDL_Quit();
}

Timer::Timer() {
    //Initialize the variables
    startTicks = 0;
    pausedTicks = 0;
    paused = false;
    started = false;
}

void Timer::start() {
    started = true;
    paused = false;
    startTicks = SDL_GetTicks();
}

void Timer::stop() {
    started = false;
    paused = false;
}

void Timer::pause() {
    if ( ( started == true ) && ( paused == false )) {
        //Pause the timer
        paused = true;
        //Calculate the paused ticks
        pausedTicks = SDL_GetTicks() - startTicks;
    }
}

void Timer::unpause() {
    if ( paused == true ) {
        //Unpause the timer
        paused = false;
        //Reset the starting ticks
        startTicks = SDL_GetTicks() - pausedTicks;
        //Reset the paused ticks;
        pausedTicks = 0;
    }
}

int Timer::get_ticks() {
    //If the timer is running
    if ( started == true ) {
        if ( paused == true ) {
            //Return the number of ticks when the timer was paused 
            return pausedTicks;
        } else {
            //Return the current time minus the start time
            return SDL_GetTicks() - startTicks;
        }
    }
    //If the timer isn't running
    return 0;
}

bool Timer::is_started() {
    return started;
}

bool Timer::is_paused() {
    return paused;
}

int main( int argc, char* args[] ) {
    bool quit = false;
    if ( init() == false ) {
        return 1;
    }

    if ( load_files() == false ) {
        return 1;
    }

    //Make the timer 
    Timer myTimer;

    //Generate the message surfaces
    startStop = TTF_RenderText_Solid( font, "Press S to start or stop the timer", textColor );
    pauseMessage = TTF_RenderText_Solid( font, "Press P to pause or unpause the timer", textColor );

    //Start the timer
    myTimer.start();

    //While the user hasn't quit
    while ( quit == false ) {
        while ( SDL_PollEvent( &event ) ) {
            if ( event.type == SDL_KEYDOWN ) {
                if ( event.key.keysym.sym == SDLK_s) {
                    if ( myTimer.is_started() == true ) {
                        myTimer.stop();
                    } else {
                        myTimer.start();
                    }
                }

                if ( event.key.keysym.sym == SDLK_p ) {
                    if ( myTimer.is_paused() == true ) {
                        myTimer.unpause();
                    } else {
                        myTimer.pause();
                    }
                }

                
            } else if ( event.type == SDL_QUIT ) {
                quit = true;
            }
        }

        apply_surface( 0, 0, background, screen );
        apply_surface( ( SCREEN_WIDTH -  startStop->w ) / 2, 200, startStop, screen );
        apply_surface( ( SCREEN_WIDTH - pauseMessage->w ) / 2, 250, pauseMessage, screen );

        //The timer's time as a string
        std::stringstream time;

        time << "Timer: " << myTimer.get_ticks() / 1000.f;

        seconds = TTF_RenderText_Solid( font, time.str().c_str(), textColor );

        apply_surface( ( SCREEN_WIDTH - seconds->w ) / 2, 0, seconds, screen );

        SDL_FreeSurface( seconds );

        if ( SDL_Flip( screen ) == -1 ) {
            return 1;
        }
        
    }

    //Clean up
    clean_up();
    return 0;
        
}
