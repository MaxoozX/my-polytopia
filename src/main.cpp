#include <cstdlib>
#include <cmath> // Need to compile with -lm
#include <cstring>
#include <cstdio>

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "MyGame.hpp"

int main(int argc, char **argv) {

    SDL_Init(SDL_INIT_EVERYTHING);

    // MyGame myGame(1200, 900, 144, 50);
    MyGame myGame(1200, 900, 60, 30);

    myGame.setup();

    myGame.start();

    myGame.destroy();

    return 0;

}