#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"
#include <string>
#include "ImageManager.h"

const int FRAME_WIDTH = 320;
const int FRAME_HEIGHT = 240;
const int ZERO = 0;

void ImageManager::draw_to_surface(SDL_Surface* source, SDL_Surface* destination ) {
	apply_surface( ZERO, ZERO, source, destination );
    apply_surface( FRAME_WIDTH, ZERO, source, destination );
    apply_surface( ZERO, FRAME_HEIGHT, source, destination );
    apply_surface( FRAME_WIDTH, FRAME_HEIGHT, source, destination );
}

void ImageManager::apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination ) {
    // Make a temporary rectangle to hold the offsets
    SDL_Rect offset;

    // Give the offsets to the rectangle
    offset.x = x;
    offset.y = y;

    // Blit the surface
    SDL_BlitSurface( source, NULL, destination, &offset );
}
