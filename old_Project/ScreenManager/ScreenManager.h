#ifndef SCREEN_MANAGER_H
#define SCREEN_MANAGER_H

#include "SDL/SDL.h"
#include <string>

class ScreenManager {
private:
public:
    SDL_Surface *load_image( std::string filename );
    void apply_surface( int x, int y, SDL_Surface *source, SDL_Surface *destination );
};
#endif /* SCREEN_MANAGER_H */




