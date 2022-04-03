/**
 * Header file for Shape class.
 * @file Shape.hpp
 * @author Maxence
 * @version 1.0
*/

#ifndef SHAPE_H
#define SHAPE_H

#include <vector>
#include <string>
#include <tuple>

class Shape {

    public:
        int m_width;
        int m_height;

        std::vector< std::vector<char> > grid; // I can't use a bool vector, it's stacked one val per digit

        int m_nbTiles;
        std::vector<int> m_nbTilesPerRow;

        Shape(int = 1, int = 1);
        void loadFromPNG(std::string);

        void rotClockwise();
        void rotCounterClockwise();

        void recountTilesPerRow();

        std::tuple<int, int, int> computeRealDimensions() const; // tuple< trueLeft, trueBottom, trueRight >

        bool removeRow(int);

};

#endif // SHAPE_H