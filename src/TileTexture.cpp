/**
 * Implementation file for the TileTexture struct.
 * @file TileTexture.cpp
 * @author Maxence
 * @version 1.0
*/

#include <string>
#include <stdexcept>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "TileTexture.hpp"

TileTexture::TileTexture(SDL_Renderer* renderer, int _width, int _height, std::string texturePath, int alpha) { // 0 <= alpha <= 255

    if(_width < 0) {
        throw std::invalid_argument("The width must be greater than 0");
    }
    width = _width;
    if(_height < 0) {
        throw std::invalid_argument("The height must be greater than 0");
    }
    height = _height;

    const char *cStr = texturePath.c_str();
    texture = IMG_LoadTexture(renderer, cStr);
    SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
    if(texture == nullptr) {
        char buffer[1024]; // The buffer is big enough so that there is no risk of overflow
        sprintf(buffer, "Problem loading the texture of the cube (%s)", IMG_GetError());
        throw std::invalid_argument(buffer);
    }
    
    SDL_SetTextureAlphaMod(texture, alpha); // Must be between 0 and 255
}

TileTexture::TileTexture() {}