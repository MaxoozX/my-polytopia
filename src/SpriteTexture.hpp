/**
 * Header file for the SpriteTexture struct.
 * @file SpriteTexture.hpp
 * @author Maxence
 * @version 1.0
*/

#ifndef TILE_TEXTURE_H
#define TILE_TEXTURE_H

#include <string>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

struct SpriteTexture {

    int width;
    int height;
    SDL_Texture* texture;

    SpriteTexture(SDL_Renderer*, int, int, std::string, int = 255);
    SpriteTexture();

};

#endif // TILE_TEXTURE_H