#include <cstdlib>
#include <cmath> // Need to compile with -lm
#include <cstring>
#include <cstdio>

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h> // To load the texture (IMG_...)

#include "Tetris.hpp"

#include "constants.hpp"

using namespace std;

int main(int argc, char **argv) {

  SDL_Init(SDL_INIT_EVERYTHING);


  Tetris game(
    constants::WIDTH_IN_PIXELS,
    constants::HEIGHT_IN_PIXELS,
    constants::FRAMERATE,
    constants::NUMBER_SHAPES,
    constants::BOARD_OFFSET_X,
    constants::BOARD_OFFSET_Y
    ); // TODO: Add a scaling factor for window size
  game.setup();
  game.start();
  game.destroy();

  return 0;
}

/*
- Add a score counter
- Add some sort of super attack
- Add sounds with SDL_Mixer
*/