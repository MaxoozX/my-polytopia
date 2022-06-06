/**
 * Header file for the Tile struct.
 * @file Tile.hpp
 * @author Maxence
 * @version 1.0
*/

#ifndef TILE_H
#define TILE_H

#include "Biomes.hpp"

#include "TileTexture.hpp"

struct Tile {

    TileTexture* texture;
    Biomes biome;

    Tile(TileTexture* _texture, Biomes _biome);
    Tile();

    void setTexturePtr(TileTexture* _texture);
    void setBiome(Biomes _biome);

};

#endif // TILE_H