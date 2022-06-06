/**
 * Header file for the Camera struct.
 * @file Camera.hpp
 * @author Maxence
 * @version 1.0
*/

#ifndef CAMERA_H
#define CAMERA_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Engine/Geometry.hpp"

struct Camera {
    double x = 0;
    double y = 0;
    int w = 0;
    int h = 0;
    int actualW = 0;
    int actualH = 0;
    int worldLeft = 0;
    int worldRight = 0;
    int worldTop = 0;
    int worldBottom = 0;
    double zoom = 1.0;

    Camera(double, double, int, int, int, int, int, int, int, int, double);
    bool transformRect(SDL_Rect*);
    Geometry::Point2d<int> getWorldCoordinates(Geometry::Point2d<int>);
    void setZoom(double);
    void move(Geometry::Vector2d<float>);

};

#endif // CAMERA_H