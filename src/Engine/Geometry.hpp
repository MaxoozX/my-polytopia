/**
 * File for basics geometric object (Points and Vectors)
 * @file Point.hpp
 * @author Maxence
 * @version 1.0
*/

#include <cmath>

#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#define PI 3.14159

#ifndef GEOMETRY_H
#define GEOMETRY_H

namespace Geometry {

    template <class NumberType>
    class Vector2d;

    // Point class
    /* -------------------------------------------------------------------------------------------- */
    /** Simple class to hold a 2D Point */
    template <class NumberType>
    class Point2d {

        public:
            NumberType x;
            NumberType y;
            Point2d(NumberType _x = 0, NumberType _y = 0): x(_x), y(_y) {}
            Point2d(const Point2d<NumberType> &otherPoint): x(otherPoint.x), y(otherPoint.y) {}
            Point2d<NumberType>& operator+=(Vector2d<NumberType> const &);
            Point2d<NumberType>& operator-=(Vector2d<NumberType> const &);

    };

    // Comparison
    /* ----------------- */
    template <class NumberType>
    bool operator==(Point2d<NumberType> const &p1, Point2d<NumberType> const &p2) {
        return (p1.x == p2.x && p1.y == p2.y);
    }

    template <class NumberType>
    bool operator!=(Point2d<NumberType> const &p1, Point2d<NumberType> const &p2) {
        return !(p1 == p2);
    }
    /* ----------------- */


    // Displaying
    /* ----------------- */
    template <class NumberType>
    std::ostream& operator<<(std::ostream& os, const Point2d<NumberType> p) {
        os << "P(" << p.x << ", " << p.y << ")";
        return os;
    }
    /* ----------------- */

    // Adding vector to points
    /* ----------------- */
    template <class NumberType>
    Point2d<NumberType>& Point2d<NumberType>::operator+=(Vector2d<NumberType> const &v) {
        x += v.x;
        y += v.y;
        return *this;
    }

    template <class NumberType>
    Point2d<NumberType>& Point2d<NumberType>::operator-=(Vector2d<NumberType> const &v) {
        x -= v.x;
        y -= v.y;
        return *this;
    }
    /* ----------------- */
    /* -------------------------------------------------------------------------------------------- */
    template <class NumberType>
    using Line2d = std::pair<Point2d<NumberType>, Point2d<NumberType> >;

    // Vector class
    /* -------------------------------------------------------------------------------------------- */
    /** Simple class to hold a 2D Vector */
    template <class NumberType>
    class Vector2d {

        public:
            NumberType x;
            NumberType y;
            Vector2d(NumberType _x = 0, NumberType _y = 0): x(_x), y(_y) {}
            Vector2d(const Vector2d<NumberType> &otherVector): x(otherVector.x), y(otherVector.y) {}

            Vector2d<NumberType>& operator+=(Vector2d<NumberType> const &);
            Vector2d<NumberType>& operator-=(Vector2d<NumberType> const &);
            Vector2d<NumberType>& operator*=(Vector2d<NumberType> const &);
            Vector2d<NumberType>& operator/=(Vector2d<NumberType> const &);
            Vector2d<NumberType>& operator*=(NumberType const &scalar);
            Vector2d<NumberType>& operator/=(NumberType const &scalar);

            NumberType euclidianNorm() const;

    };

    // In-place operations with vector
    /* ----------------- */
    template <class NumberType>
    Vector2d<NumberType>& Vector2d<NumberType>::operator+=(Vector2d<NumberType> const &v2) {
        x += v2.x;
        y += v2.y;
        return *this;
    }

    template <class NumberType>
    Vector2d<NumberType>& Vector2d<NumberType>::operator-=(Vector2d<NumberType> const &v2) {
        x -= v2.x;
        y -= v2.y;
        return *this;
    }

    template <class NumberType>
    Vector2d<NumberType>& Vector2d<NumberType>::operator*=(Vector2d<NumberType> const &v2) {
        x *= v2.x;
        y *= v2.y;
        return *this;
    }

    template <class NumberType>
    Vector2d<NumberType>& Vector2d<NumberType>::operator/=(Vector2d<NumberType> const &v2) {
        x /= v2.x;
        y /= v2.y;
        return *this;
    }
    /* ----------------- */

    // In-place operations with scalar
    /* ----------------- */
    template <class NumberType>
    Vector2d<NumberType>& Vector2d<NumberType>::operator*=(NumberType const &scalar) {
        x *= scalar;
        y *= scalar;
        return *this;
    }

    template <class NumberType>
    Vector2d<NumberType>& Vector2d<NumberType>::operator/=(NumberType const &scalar) {
        x /= scalar;
        y /= scalar;
        return *this;
    }

    template <class NumberType>
    Vector2d<NumberType> operator*(Vector2d<NumberType> const &v1, NumberType const &scalar) {
        return Vector2d<NumberType>(v1.x * scalar, v1.y * scalar);
    }

    template <class NumberType>
    Vector2d<NumberType> operator/(Vector2d<NumberType> const &v1, NumberType const &scalar) {
        return Vector2d<NumberType>(v1.x / scalar, v1.y / scalar);
    }
    /* ----------------- */

    // Binary operations
    /* ----------------- */
    template <class NumberType>
    Vector2d<NumberType> operator+(Vector2d<NumberType> const &v1, Vector2d<NumberType> const &v2) {
        return Vector2d<NumberType>(v1.x + v2.x, v1.y + v2.y);
    }

    template <class NumberType>
    Vector2d<NumberType> operator-(Vector2d<NumberType> const &v1, Vector2d<NumberType> const &v2) {
        return Vector2d<NumberType>(v1.x - v2.x, v1.y - v2.y);
    }

    template <class NumberType>
    Vector2d<NumberType> operator*(Vector2d<NumberType> const &v1, Vector2d<NumberType> const &v2) {
        return Vector2d<NumberType>(v1.x * v2.x, v1.y * v2.y);
    }

    template <class NumberType>
    Vector2d<NumberType> operator/(Vector2d<NumberType> const &v1, Vector2d<NumberType> const &v2) {
        return Vector2d<NumberType>(v1.x / v2.x, v1.y / v2.y);
    }
    /* ----------------- */

    // Unary minus (-)
    /* ----------------- */
    template <class NumberType>
    Vector2d<NumberType> operator-(Vector2d<NumberType> const &v) {
        return Vector2d<NumberType>(-v.x, -v.y);
    }
    /* ----------------- */

    // Comparison
    /* ----------------- */
    template <class NumberType>
    bool operator==(Vector2d<NumberType> const &v1, Vector2d<NumberType> const &v2) {
        return (v1.x == v2.x && v1.y == v2.y);
    }

    template <class NumberType>
    bool operator!=(Vector2d<NumberType> const &v1, Vector2d<NumberType> const &v2) {
        return !(v1 == v2);
    }
    /* ----------------- */

    // Displaying vector
    /* ----------------- */
    template <class NumberType>
    std::ostream& operator<<(std::ostream& os, const Vector2d<NumberType> p) {
        os << "V(" << p.x << ", " << p.y << ")";
        return os;
    }
    /* ----------------- */

    // Useful functions
    /* ----------------- */
    template <class NumberType>
    NumberType Vector2d<NumberType>::euclidianNorm() const {
        return sqrt(pow(x, 2) + pow(y, 2));
    }

    template <class NumberType>
    NumberType DotProduct(const Vector2d<NumberType> &a, const Vector2d<NumberType> &b) {
        return ((a.x * b.x) + (a.y * b.y));
    }

    template <class NumberType>
    NumberType CrossProduct(const Vector2d<NumberType> &a, const Vector2d<NumberType> &b) {
        return ((a.x * b.y) - (a.y * b.x));
    }
    /* ----------------- */

    // Polygon class
    /* -------------------------------------------------------------------------------------------- */
    /** A class to store a polygon, stores the vertices and then can compute center, side and diagonals */
    template <class NumberType>
    class Polygon {

        public:
          int m_w;
          int m_h;
          std::vector<Point2d<NumberType> > vertices; // Must be at least 3 vertices
          Point2d<NumberType> midPoint;
          std::vector<std::pair<Point2d<NumberType>, Point2d<NumberType> > > sides;
          std::vector<std::pair<Point2d<NumberType>, Point2d<NumberType> > > diagonals;
          Polygon() {}
          Polygon(const Polygon<NumberType> &otherPolygon): m_w(otherPolygon.m_w), m_h(otherPolygon.m_h), vertices(otherPolygon.vertices), sides(otherPolygon.sides) {}
          bool checkValidity();
          void computeMidPoint();
          void computeSidesAndDiagonals();
    };

    // Useful functions
    /* ----------------- */
    template <class NumberType>
    bool Polygon<NumberType>::checkValidity() {
        return (vertices.size() >= 3);
    }

    template <class NumberType>
    bool lessClockwise(Point2d<NumberType> a, Point2d<NumberType> b, Point2d<NumberType> center) {
        if (a.x - center.x >= 0 && b.x - center.x < 0)
            return true;
        if (a.x - center.x < 0 && b.x - center.x >= 0)
            return false;
        if (a.x - center.x == 0 && b.x - center.x == 0) {
            if (a.y - center.y >= 0 || b.y - center.y >= 0)
                return a.y > b.y;
            return b.y > a.y;
        }

        // compute the cross product of vectors (center -> a) x (center -> b)
        int det = (a.x - center.x) * (b.y - center.y) - (b.x - center.x) * (a.y - center.y);
        if (det < 0)
            return true;
        if (det > 0)
            return false;

        // points a and b are on the same line from the center
        // check which point is closer to the center
        int d1 = (a.x - center.x) * (a.x - center.x) + (a.y - center.y) * (a.y - center.y);
        int d2 = (b.x - center.x) * (b.x - center.x) + (b.y - center.y) * (b.y - center.y);
        return d1 > d2;
    }

    template <class NumberType>
    void Polygon<NumberType>::computeMidPoint() {

        NumberType minX, maxX, minY, maxY, curX, curY;
        minX = vertices[0].x;
        maxX = vertices[0].x;
        minY = vertices[0].y;
        maxY = vertices[0].y;

        for(unsigned int index = 1; index < vertices.size(); index++) {
            curX = vertices[index].x;
            curY = vertices[index].y;

            if(curX > maxX) maxX = curX;
            else if(curX < minX) minX = curX;

            if(curY > maxY) maxY = curY;
            else if(curY < minY) minY = curY;
        }

        midPoint.x = minX + (maxX - minX) / 2;
        midPoint.y = minY + (maxY - minY) / 2;

        // Sort the vertices in clockwise order so that we can join them and create sides
        std::sort(vertices.begin(), vertices.end(), [&](Point2d<NumberType> &p1, Point2d<NumberType> &p2) {
            return lessClockwise<NumberType>(p1, p2, midPoint);
        });

    }

    // Always call computeMidPoint before this method
    template <class NumberType>
    void Polygon<NumberType>::computeSidesAndDiagonals() {
        sides.clear();
        diagonals.clear();
        for(int index = 0; index < vertices.size(); index++) {
          sides.push_back(std::make_pair(vertices[index], vertices[(index+1)%vertices.size()]));
          diagonals.push_back(std::make_pair(midPoint, vertices[(index+1)%vertices.size()]));
        }
    }
    /* ----------------- */

    template <class NumberType>
    std::pair<bool, Point2d<NumberType>* > checkLineCollision(Line2d<NumberType> line1, Line2d<NumberType> line2) {

        /*
        The algorithm consits of 3 steps

        1.  If the lines are parrallels -> False
        2.  Find the point where the 2 lines would cross if they were infinite
        3.  If the point does not belong to any of the 2 lines -> False
            Else the lines are colliding, their collision point exists.

        */

        double deltaX1 = line1.second.x - line1.first.x;
        double deltaY1 = line1.second.y - line1.first.y;
        double slope1 = deltaY1 / deltaX1;
        double offset1 = line1.first.y - (line1.first.x * slope1);

        double deltaX2 = line2.second.x - line2.first.x;
        double deltaY2 = line2.second.y - line2.first.y;
        double slope2 = deltaY2 / deltaX2;
        double offset2 = line2.first.y - (line2.first.x * slope2);

        // 1.
        if(slope2 == slope1) {
            return std::make_pair(false, nullptr);
        }

        // 2.
        double intersectionX = (offset2 - offset1) / (slope1 - slope2);

        int line1minX = std::min(line1.first.x, line1.second.x);
        int line1maxX = std::max(line1.first.x, line1.second.x);
        int line2minX = std::min(line2.first.x, line2.second.x);
        int line2maxX = std::max(line2.first.x, line2.second.x);

        if(line1minX <= intersectionX && intersectionX <= line1maxX && line2minX <= intersectionX && intersectionX <= line2maxX) {
            return std::make_pair(true, new Point2d<NumberType>(intersectionX, slope1 * intersectionX + offset1));
        }

        return std::make_pair(false, nullptr);

    }

    template <class NumberType>
    std::pair<bool, Point2d<NumberType>* > checkPolygonCollision(Polygon<NumberType> &polygon1, Polygon<NumberType> &polygon2) {
      
        for(auto side: polygon1.sides) {
            for(auto diagonal: polygon2.diagonals) {
                std::pair<bool, Point2d<NumberType>* > result = checkLineCollision(side, diagonal);
                if(result.first) {
                    return result;
                }
            }
        }

        for(auto side: polygon2.sides) {
            for(auto diagonal: polygon1.diagonals) {
                std::pair<bool, Point2d<NumberType>* > result = checkLineCollision(side, diagonal);
                if(result.first) {
                    return result;
                }
            }
        }

        return std::make_pair(false, nullptr);

    }

    template <class NumberType>
    Polygon<NumberType> getPolygonFromPNG(const char path[]) {
        Polygon<NumberType> polygon;
        SDL_Surface *surface = IMG_Load(path);
        if(surface == nullptr) {
            SDL_Log("Impossible to load the image");
            return polygon;
        }
        int *pixels = (int*)surface->pixels;
        polygon.m_w = surface->w;
        polygon.m_h = surface->h;
        for(int row = 0; row < surface->h; row++) {
            for(int column = 0; column < surface->w; column++) {
                int pixel = pixels[row*surface->w+column];
                int alpha = (pixel >> 24) & 0xFF;
                // int red = (pixel >> 16) & 0xFF;
                // int green = (pixel >> 8) & 0xFF;
                // int blue = pixel & 0xFF;
                if(alpha > 0) {
                    polygon.vertices.push_back(Point2d<NumberType>(column, row));
                }
            }
        }
        return polygon;
    }
}

#endif // GEOMETRY_H