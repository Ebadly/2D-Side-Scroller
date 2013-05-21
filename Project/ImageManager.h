#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"
#include <string>

class ImageManager {
private:
	void apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination );
public:
	void draw_to_surface( SDL_Surface* source, SDL_Surface* destination );
};
