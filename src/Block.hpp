/**
 * Header file for Block class.
 * @file Block.hpp
 * @author Maxence
 * @version 1.0
*/

#ifndef BLOCK_H
#define BLOCK_H

#include <SDL2/SDL.h>

#include "Engine/Geometry.hpp"
#include "Engine/Color.hpp"
#include "Engine/Sprite.hpp"

#include "Shape.hpp"

class Block : public Sprite {
    
    private:

        int m_windowWidth;
        int m_windowHeight;

        Shape m_shape;

    public:
        int m_shapeIndex;
        int m_x;
        int m_y;
        int m_trueLeft;
        int m_trueRight;
        int m_trueBottom;
        int m_rotation;

        Color m_color;

        Block(SDL_Renderer* = nullptr, int = 0, int = 0, int = 0, int = 0, int = 2 );
        void load();
        void draw(int = 0, int = 0) const;
        void rotate();
        void rotateBack();

        bool doesOverlap(Block &) const;

        void updateRealDimensions();
        void matchDimensionsToShape();

        bool removeRow(int); // True if the block's shape is empty

        int getNbTilesRow(int);

};

#endif // BLOCK_H