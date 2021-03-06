/**
 * Header file for Block class.
 * @file Block.hpp
 * @author Maxence
 * @version 1.0
*/

#ifndef BLOCK_H
#define BLOCK_H

#include <vector>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "Engine/Geometry.hpp"
#include "Engine/Color.hpp"
#include "Engine/Sprite.hpp"

#include "Shape.hpp"
#include "constants.hpp"

class Block : public Sprite {
    
    private:

        int m_windowWidth;
        int m_windowHeight;

        Shape m_shape;

        std::vector<SDL_Texture*>* m_faceTextures;

    public:
        int m_shapeIndex;
        int m_x;
        int m_y;
        int m_trueLeft;
        int m_trueRight;
        int m_trueBottom;
        int m_rotation;

        Color m_color;

        Constants* constants;

        Block(SDL_Renderer* = nullptr, int = 0, int = 0, int = 0, int = 0, int = 2, std::vector<SDL_Texture*>* = nullptr, Constants* = nullptr);
        void load();
        void draw(int = 0, int = 0, bool = false) const;
        void rotate();
        void rotateBack();

        bool doesOverlap(Block &) const;

        void updateRealDimensions();
        void matchDimensionsToShape();

        bool removeRow(int); // True if the block's shape is empty

        int getNbTilesRow(int);

};

#endif // BLOCK_H