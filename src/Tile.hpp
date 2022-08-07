/**
 * Header file for the Tile struct.
 * @file Tile.hpp
 * @author Maxence
 * @version 1.0
*/

#ifndef TILE_H
#define TILE_H

#include "Biomes.hpp"

#include "SpriteTexture.hpp"

struct Tile {

    SpriteTexture* texture;
    Biomes biome;

    Tile(SpriteTexture* _texture, Biomes _biome);
    Tile();

    void setTexturePtr(SpriteTexture* _texture);
    void setBiome(Biomes _biome);

};

#endif // TILE_H