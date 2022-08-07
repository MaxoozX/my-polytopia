/**
 * Header file for the Player class.
 * @file Player.hpp
 * @author Maxence
 * @version 1.0
*/

#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "SpriteTexture.hpp"

struct Player {

    int tileX;
    int tileY;

    SpriteTexture* texture;

    Player(int, int, SpriteTexture*);

    Player();

    /*
    Things I want to add :
        - Facing : Direction { North, South, East, West}
        - Object in hand
        - Action
        -> Adding animations
    */

};

#endif // PLAYER_HPP