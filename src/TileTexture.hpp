/**
 * Header file for the TileTexture struct.
 * @file TileTexture.hpp
 * @author Maxence
 * @version 1.0
*/

#ifndef TILE_TEXTURE_H
#define TILE_TEXTURE_H

#include <string>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

struct TileTexture {

    int width;
    int height;
    SDL_Texture* texture;

    TileTexture(SDL_Renderer*, int, int, std::string, int = 255);
    TileTexture();

};

#endif // TILE_TEXTURE_H