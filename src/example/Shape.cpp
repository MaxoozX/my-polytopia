/**
 * Implementation file for Shape class.
 * @file Shape.cpp
 * @author Maxence
 * @version 1.0
*/

#include <vector>
#include <string>
#include <tuple>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "Shape.hpp"

#include "exceptions.hpp"

Shape::Shape(int width, int height):
    m_width(width), m_height(height),
    grid(height, std::vector<char>(width, 1)),
    m_nbTiles(0), m_nbTilesPerRow(height, 0)
    {}

void Shape::loadFromPNG(std::string pathToPNG) {

    SDL_Surface *surface = IMG_Load(pathToPNG.c_str());

    int *pixels = (int*)surface->pixels;

    for(int row = 0; row < m_height; row++) {
        for(int column = 0; column < m_width; column++) {
            int pixel = pixels[row*surface->w+column];
            int alpha = (pixel >> 24) & 0xFF;
            // int red = (pixel >> 16) & 0xFF;
            // int green = (pixel >> 8) & 0xFF;
            // int blue = pixel & 0xFF;

            if(alpha != 0) {
                grid[row][column] = 1;
                m_nbTiles++;
            } else {
                grid[row][column] = 0;
            }
        }
    }

    recountTilesPerRow();

}

void Shape::recountTilesPerRow() {

    for(int row = 0; row < m_height; row++) {

        m_nbTilesPerRow[row] = 0;

        for(int column = 0; column < m_width; column++) {

            if(grid[row][column] != 0) {
                m_nbTilesPerRow[row]++;
            }
        }
    }
}

void Shape::rotClockwise() {

    int oldWidth = m_width;
    int oldHeight = m_height;

    m_width = oldHeight;
    m_height = oldWidth;

    std::vector< std::vector<char> > gridCopy(m_height, std::vector<char>(m_width, 0));

    for(int row = 0; row < m_height; row++) {
        for(int column = 0; column < m_width; column++) {

            gridCopy[row][column] = grid[m_width-column-1][row];

        }
    }

    grid = gridCopy;

    recountTilesPerRow();

}

void Shape::rotCounterClockwise() {

    int oldWidth = m_width;
    int oldHeight = m_height;

    m_width = oldHeight;
    m_height = oldWidth;

    std::vector< std::vector<char> > gridCopy(m_height, std::vector<char>(m_width, 0));

    for(int row = 0; row < m_height; row++) {
        for(int column = 0; column < m_width; column++) {

            // gridCopy[row][column] = grid[m_width-column-1][row];
            gridCopy[row][column] = grid[column][m_height-row-1];

        }
    }

    grid = gridCopy;

    recountTilesPerRow();

}

std::tuple<int, int, int> Shape::computeRealDimensions() const {
    // Get the real dimensions of the spape, O(MN)

    int left = 1000; // A bigger value than any shape dimension
    int bottom = -1;
    int right = -1;

    for(int row = 0; row < m_height; row++) {
        for(int column = 0; column < m_width; column++) {

            if(grid[row][column] != 0) {

                if(row > bottom) {
                    bottom = row;
                }
                if(column > right) {
                    right = column;
                }
                if(column < left) {
                    left = column;
                }

            }

        }
    }

    if(
        left > m_width ||
        right < 0 ||
        bottom < 0
    ) {
        SDL_Log("Invalid shape when recomputing dimensions");
        throw err::InvalidShape();
    }

    return std::make_tuple(left, bottom, right);

}

bool Shape::removeRow(int rowToRemove) {

    if(rowToRemove > m_height || rowToRemove < 0 || m_nbTilesPerRow[rowToRemove] <= 0) return false;

    // Remove the row
    for(int column = 0; column < m_width; column++) {
        if(grid[rowToRemove][column] == 0) continue;
        
        grid[rowToRemove][column] = 0;
        m_nbTiles--;
    }

    grid.erase(grid.begin() + rowToRemove);

    m_nbTilesPerRow.erase(m_nbTilesPerRow.begin() + rowToRemove);

    m_height--;

    return true;

}