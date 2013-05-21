#ifndef DOT_H
#define DOT_H

#include <iostream>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include <vector>
#include <string>
#include <cmath>
#include "Circle.h"

class Dot {
    private:
        //The area of the dot
        Circle c;

        //The velocity of the dot
        int xVel, yVel;

    public:
        //Initialize the variables
        Dot();

        //Take key presses and adjust the dot's velocity
        void handle_input();

        //Moves the dot
        void move( std::vector<SDL_Rect> &rects, Circle &circle );

        //Shows the dot on the screen
        void show();
};

#endif /* DOT_H */
