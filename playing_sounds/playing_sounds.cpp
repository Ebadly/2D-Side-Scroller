//The headers
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"
#include "SDL/SDL_mixer.h"
#include <string>

//Screen attributes
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int SCREEN_BPP = 32;


//The surfaces
SDL_Surface *background = NULL;
SDL_Surface *message = NULL;
SDL_Surface *screen = NULL;


//The event structure
SDL_Event event;

//The font
TTF_Font *font = NULL;

//The color of the font
SDL_Color textColor = { 0, 0, 0 };

//The music that will be played
Mix_Music *music = NULL;

//The sound effects that will be used
Mix_Chunk *scratch = NULL;
Mix_Chunk *high = NULL;
Mix_Chunk *med = NULL;
Mix_Chunk *low = NULL;

SDL_Surface *load_image( std::string filename ) {
    //The image that's loaded
    SDL_Surface* loadedImage = NULL;

    //The optimized surface that will be used
    SDL_Surface* optimizedImage = NULL;

    //Load the image
    loadedImage = IMG_Load( filename.c_str() );

    //If the image loaded
    if( loadedImage != NULL )
    {
        //Create an optimized surface
        optimizedImage = SDL_DisplayFormat( loadedImage );

        //Free the old surface
        SDL_FreeSurface( loadedImage );

        //If the surface was optimized
        if( optimizedImage != NULL )
        {
            //Color key surface
            SDL_SetColorKey( optimizedImage, SDL_SRCCOLORKEY, SDL_MapRGB( optimizedImage->format, 0, 0xFF, 0xFF ) );
        }
    }

    //Return the optimized surface
    return optimizedImage;
}

void apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip = NULL ) {
    //Holds offsets
    SDL_Rect offset;

    //Get offsets
    offset.x = x;
    offset.y = y;

    //Blit
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

    if ( Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 4096 ) == -1 ) {
        return false;
    }

    SDL_WM_SetCaption( "Monitor Music", NULL );

    return true;
}

bool load_files() {
    background = load_image( "background.png" );
    font = TTF_OpenFont( "lazy.ttf", 30 );

    if ( background == NULL ) {
        return false;
    }

    if ( font == NULL ) {
        return false;
    }

    music = Mix_LoadMUS( "beat.wav" );

    if ( music == NULL ) {
        return false;
    }

    scratch = Mix_LoadWAV( "scratch.wav" );
    high = Mix_LoadWAV( "high.wav" );
    med = Mix_LoadWAV( "medium.wav" );
    low = Mix_LoadWAV( "low.wav" );

    if ( scratch == NULL || high == NULL || med == NULL || low == NULL ) {
        return false;
    }

    return true;
}

void clean_up() {
    SDL_FreeSurface( background );
    Mix_FreeChunk( scratch );
    Mix_FreeChunk( high );
    Mix_FreeChunk( med );
    Mix_FreeChunk( low );

    Mix_FreeMusic( music );
    TTF_CloseFont( font );
    Mix_CloseAudio();
    TTF_Quit();
    SDL_Quit();
}

int main( int argc, char* args[] ) {
    bool quit = false;
    if ( init() == false ) {
        return 1;
    }

    if ( load_files() == false ) {
        return 1;
    }

    apply_surface( 0,0,background,screen );

    message = TTF_RenderText_Solid( font, "Press 1,2,3, or 4 to play a sound effect.", textColor );

    if ( message == NULL ) {
        return 1;
    }

    apply_surface( (SCREEN_WIDTH - message->w) / 2, 100, message, screen );

    SDL_FreeSurface( message );

    message = TTF_RenderText_Solid( font, "Press 9 to play or pause music", textColor );

    if ( message == NULL ) {
        return 1;
    }

    apply_surface(  (SCREEN_WIDTH - message->w ) / 2, 200, message, screen );
    SDL_FreeSurface( message );

    message = TTF_RenderText_Solid( font, "Press 0 to stop the music", textColor );

    if ( message == NULL ) {
        return 1;
    }

    apply_surface( ( SCREEN_WIDTH - message->w ) / 2, 300, message, screen );

    SDL_FreeSurface( message );

    if ( SDL_Flip( screen ) == - 1) {
        return 1;
    }

    while ( quit == false ) {
        while ( SDL_PollEvent( &event ) ) {
            if ( event.type == SDL_KEYDOWN ) {
                if ( event.key.keysym.sym == SDLK_1 ) {
                    if ( Mix_PlayChannel( -1, scratch, 0 ) == -1 ) {
                        return 1;
                    }
                } else if ( event.key.keysym.sym == SDLK_2 ) {
                    if ( Mix_PlayChannel( -1, high, 0 ) == -1 ) {
                        return 1;
                    }
                } else if ( event.key.keysym.sym == SDLK_3 ) {
                    if ( Mix_PlayChannel( -1, med, 0 ) == -1 ) {
                        return 1;
                    }
                } else if ( event.key.keysym.sym == SDLK_4 ) {
                    if ( Mix_PlayChannel( -1, low, 0 ) == -1 ) {
                        return 1;
                    }
                } else if ( event.key.keysym.sym == SDLK_9 ) {
                    if ( Mix_PlayingMusic() == 0 ) {
                        if ( Mix_PlayMusic( music, -1 ) == -1 ) {
                            return 1;
                        }
                    } else {
                        if ( Mix_PausedMusic() == 1 ) {
                            Mix_ResumeMusic();
                        } else {
                            Mix_PauseMusic();
                        }
                    }
                } else if ( event.key.keysym.sym == SDLK_0 ) {
                    Mix_HaltMusic();
                }
            }

            if ( event.type == SDL_QUIT ) {
                quit = true;
            }
        }
    }

    clean_up();
    return 0;
}

