#include "ScreenManager.h"
#include "SDL/SDL_image.h"

// TEST * before or after
SDL_Surface *ScreenManager::load_image( std::string filename ) {
    //temporary storage for the image that's loaded
    SDL_Surface *loadedImage = NULL;
    SDL_Surface *optimizedImage = NULL;
    if ( loadedImage != NULL ) {
        optimizedImage = SDL_DisplayFormat( loadedImage );
        SDL_FreeSurface( loadedImage );
    }
    return optimizedImage;
}


void ScreenManager::apply_surface( int x, int y, SDL_Surface *source, SDL_Surface *destination ) {
    // Make a temporary rectangle to hold the offsets
    SDL_Rect offset;

    // Give the offsets to the rectangle
    offset.x = x;
    offset.y = y;

    // Blit the surface
    SDL_BlitSurface( source, NULL, destination, &offset );
}


        
