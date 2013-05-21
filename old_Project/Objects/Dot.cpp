#include "Dot.h"

const int DOT_WIDTH = 20;

Dot::Dot() {
    //Initialize the offsets and dimentions
    c.x = DOT_WIDTH / 2;
    c.y = DOT_WIDTH / 2;
    c.r = DOT_WIDTH / 2;

    //Initialize the velocity
    xVel = 0;
    yVel = 0;
}

void Dot::handle_input() {
    //*** Might have to pass in the event variable ***//

    //If a key was pressed
    if( event.type == SDL_KEYDOWN ) {
        //Adjust the velocity
        switch( event.key.keysym.sym ) {
            case SDLK_UP: yVel -= 1; break;
            case SDLK_DOWN: yVel += 1; break;
            case SDLK_LEFT: xVel -= 1; break;
            case SDLK_RIGHT: xVel += 1; break;
        }
    } else if( event.type == SDL_KEYUP ) {
        //Adjust the velocity
        switch( event.key.keysym.sym ) {
            case SDLK_UP: yVel += 1; break;
            case SDLK_DOWN: yVel -= 1; break;
            case SDLK_LEFT: xVel += 1; break;
            case SDLK_RIGHT: xVel -= 1; break;
        }
    }
}

void Dot::move( std::vector<SDL_Rect> &rects, Circle &circle ) {
    //Move the dot left or right
    c.x += xVel;

    //If the dot went too far to the left or right or has collided with the other shapes
    if( ( c.x - DOT_WIDTH / 2 < 0 ) || ( c.x + DOT_WIDTH / 2 > SCREEN_WIDTH ) || ( check_collision( c, rects ) ) || ( check_collision( c, circle ) ) ) {
        //Move back
        c.x -= xVel;
    }

    //Move the dot up or down
    c.y += yVel;

    //If the dot went too far up or down or has collided with the other shapes
    if( ( c.y - DOT_WIDTH / 2 < 0 ) || ( c.y + DOT_WIDTH / 2 > SCREEN_HEIGHT ) || ( check_collision( c, rects ) ) || ( check_collision( c, circle ) ) ) {
        //Move back
        c.y -= yVel;
    }
}

void Dot::show() {
    //Show the dot
    apply_surface( c.x - c.r, c.y - c.r, dot, screen );
}

