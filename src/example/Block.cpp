/**
 * Implementation file for Block class.
 * @file Block.cpp
 * @author Maxence
 * @version 1.0
*/

#include <cstdlib>

#include <fstream>
#include <tuple>
#include <filesystem>

#include <SDL2/SDL.h>

#include "Engine/Sprite.hpp"
#include "Engine/json.hpp"

#include "constants.hpp"

#include "Shape.hpp"
#include "Block.hpp"


using json = nlohmann::json;
namespace fs = std::filesystem;


Block::Block(SDL_Renderer* renderer, int windowWidth, int windowHeight, int x, int y, int shapeIndex, std::vector<SDL_Texture*> *faceTextures, Constants* ptrConstants):
    Sprite::Sprite(x, y, 0, 0, renderer, 10),
    m_shapeIndex(shapeIndex), m_x(x), m_y(y),
    m_trueLeft(0), m_trueRight(0), m_trueBottom(0),
    m_rotation(0), m_color(0, 0, 0, 1.0),
    m_faceTextures(faceTextures), constants(ptrConstants)
    {}

void Block::load() {

    std::filesystem::path shapePath;

    if (m_shapeIndex == constants->PIECE_I) {
        shapePath = constants->assetsPath / "1";
        m_color = Color(0, 255, 255, 1.0);
    } else if (m_shapeIndex == constants->PIECE_O) {
        shapePath = constants->assetsPath / "2";
        m_color = Color(255, 215, 0, 1.0);
    } else if (m_shapeIndex == constants->PIECE_Z) {
        shapePath = constants->assetsPath / "3";
        m_color = Color(220, 20, 60, 1.0);
    } else if (m_shapeIndex == constants->PIECE_S) {
        shapePath = constants->assetsPath / "4";
        m_color = Color(50, 205, 50, 1.0);
    } else if (m_shapeIndex == constants->PIECE_J) {
        shapePath = constants->assetsPath / "5";
        m_color = Color(0, 0, 205, 1.0);
    } else if (m_shapeIndex == constants->PIECE_L) {
        shapePath = constants->assetsPath / "6";
        m_color = Color(255, 140, 0, 1.0);
    } else if (m_shapeIndex == constants->PIECE_T) {
        shapePath = constants->assetsPath / "7";
        m_color = Color(255, 105, 180, 1.0);
    } else {
        SDL_Log("Can't match the shape %d with a known shape", m_shapeIndex);
        throw std::runtime_error("Shape path isn't defined because the shape can't be found");
    }
    
    const std::filesystem::path texturePath = shapePath / "shape.png";
    const std::filesystem::path infoPath = shapePath / "info.json";


    if(!fs::exists(texturePath)) {
        SDL_Log("Impossible to find the following texture file : %s", texturePath.string().c_str());
        throw std::runtime_error("Impossible to load texture file");
    }

    if(!fs::exists(infoPath)) {
        SDL_Log("Impossible to find the following data file : %s", infoPath.string().c_str());
        throw std::runtime_error("Impossible to load data file");
    }

    // Read JSON file
    std::ifstream file(infoPath);
    json data;
    file >> data;

    m_width = data["width"].get<int>();
    m_height = data["height"].get<int>();

    m_rect.w = m_width;
    m_rect.h = m_height;

    m_shape = Shape(m_width, m_height);
    m_shape.loadFromPNG(texturePath.string().c_str());

    updateRealDimensions();

}

void Block::draw(int offsetX, int offsetY, bool preventFaces) const {

    // TODO: New rect for the face selection

    SDL_Rect faceRect;
    faceRect.w = constants->CELL_WIDTH_FOR_FACES;
    faceRect.h = constants->CELL_WIDTH_FOR_FACES;

    SDL_Rect rect;
    rect.w = constants->CELL_SIZE - constants->BORDER_SIZE;
    rect.h = rect.w;

    m_color.setRendererDrawColor(m_renderer);

    for(int row = 0; row < m_shape.m_height; row++) {
        for(int column = 0; column < m_shape.m_width; column++) {

            if(m_shape.grid[row][column] != 0) {

                int actualX = (m_x + column);
                int actualY = (m_y + row);
            
                rect.x = actualX * constants->CELL_SIZE + offsetX;
                rect.y = actualY * constants->CELL_SIZE + offsetY;

                std::div_t faceCol = div(actualX, 5);
                std::div_t faceRow = div(actualY, 5);

                faceRect.x = faceCol.rem * constants->CELL_WIDTH_FOR_FACES;
                faceRect.y = faceRow.rem * constants->CELL_WIDTH_FOR_FACES;

                int faceIndex = faceRow.quot;

                if(faceCol.quot >= 1) faceIndex += 5;

                if(faceRow.quot >= 0 && !preventFaces) {
                    SDL_RenderCopy(m_renderer, (*m_faceTextures)[faceIndex], &faceRect, &rect);
                } else {
                    SDL_RenderFillRect(m_renderer, &rect);
                }
                

            }
        }
    }
}

void Block::matchDimensionsToShape() {

    // Change the dimension of the block
    m_width = m_shape.m_width;
    m_height = m_shape.m_height;

    m_rect.w = m_width;
    m_rect.h = m_height;

    updateRealDimensions();

    m_rotation = (4 + m_rotation - 1) % 4; // +4 to prevent negative value being a problem

}

void Block::updateRealDimensions() {

    std::tuple<int, int, int> realDimensions = m_shape.computeRealDimensions();

    m_trueLeft = std::get<0>(realDimensions);
    m_trueBottom = std::get<1>(realDimensions);
    m_trueRight = std::get<2>(realDimensions);

}

void Block::rotate() {

    m_shape.rotClockwise();

    matchDimensionsToShape();

}

void Block::rotateBack() {

    m_shape.rotCounterClockwise();

    matchDimensionsToShape();    

}

bool Block::doesOverlap(Block &otherBlock) const {

    int other_x = otherBlock.m_x;
    int other_sec_x = other_x + otherBlock.m_width;

    int other_y = otherBlock.m_y;
    int other_sec_y = other_y + otherBlock.m_height;

    int sec_x = m_x + m_width;
    int sec_y = m_y + m_height;

    // Simply check if the two rects overlap
    if(!(
        (
            (other_x >= m_x && other_x <= sec_x)
            ||
            (other_sec_x >= m_x && other_sec_x <= sec_x)
        )
        &&
        (
            (other_y >= m_y && other_y <= sec_y)
            ||
            (other_sec_y >= m_y && other_sec_y <= sec_y)
        )
    )) return false;

    // If so, check for every square with every square O(W*H)
    for(int row = 0; row < m_shape.m_height; row++) {
        for(int column = 0; column < m_shape.m_width; column++) {

            if(m_shape.grid[row][column] != 0) {
            
                // Check for the correspondant cell
                int actual_x = m_x + column;
                int actual_y = m_y + row;

                int supposed_other_col = actual_x - other_x;
                int supposed_other_row = actual_y - other_y;

                if(
                    supposed_other_col < otherBlock.m_width && 
                    supposed_other_col >= 0 &&
                    supposed_other_row < otherBlock.m_height &&
                    supposed_other_row >= 0
                ) {
                    if(otherBlock.m_shape.grid[supposed_other_row][supposed_other_col] != 0) {

                        // SDL_Log("Collision at : %d %d", supposed_other_row, supposed_other_col);

                        return true;
                    }
                }
            } 
        }
    }

    return false;

}

bool Block::removeRow(int rowToRemove) {

    // SDL_Log("Trying to remove row : %d of shape sized : %d", rowToRemove, m_trueBottom);

    // Change the shape
    if(m_shape.removeRow(rowToRemove)) {

        // Offset the position to make sure the piece stays at the right place
        m_y++;

        m_height--;

    }

    if(m_shape.m_nbTiles > 0) {
        matchDimensionsToShape();
        return false;
    }
    
    return true;

}

int Block::getNbTilesRow(int row) {
    return m_shape.m_nbTilesPerRow[row];
}
