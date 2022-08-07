/**
 * Implementation file for the Player class.
 * @file Player.hpp
 * @author Maxence
 * @version 1.0
*/

#include "Player.hpp"

#include "SpriteTexture.hpp"

Player::Player(int x, int y, SpriteTexture* _texture): tileX(x), tileY(y), texture(_texture)  {}

Player::Player() {}