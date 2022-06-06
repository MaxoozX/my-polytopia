/**
 * Implementation file for the Tile struct.
 * @file Tile.cpp
 * @author Maxence
 * @version 1.0
*/

#include "TileTexture.hpp"
#include "Tile.hpp"

Tile::Tile(TileTexture* _texture, Biomes _biome): texture(_texture), biome(_biome) {}

Tile::Tile() {}

void Tile::setTexturePtr(TileTexture* _texture) {
    texture = _texture;
}

void Tile::setBiome(Biomes _biome) {
    biome = _biome;
}