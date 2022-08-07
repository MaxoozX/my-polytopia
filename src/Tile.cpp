/**
 * Implementation file for the Tile struct.
 * @file Tile.cpp
 * @author Maxence
 * @version 1.0
*/

#include "SpriteTexture.hpp"
#include "Tile.hpp"

Tile::Tile(SpriteTexture* _texture, Biomes _biome): texture(_texture), biome(_biome) {}

Tile::Tile() {}

void Tile::setTexturePtr(SpriteTexture* _texture) {
    texture = _texture;
}

void Tile::setBiome(Biomes _biome) {
    biome = _biome;
}