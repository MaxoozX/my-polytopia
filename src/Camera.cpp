/**
 * Implementation file for the Camera struct.
 * @file Camera.hpp
 * @author Maxence
 * @version 1.0
*/

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Engine/Geometry.hpp"

#include "Camera.hpp"

using namespace Geometry;

Camera::Camera(double _x, double _y, int _w, int _h, int _actualW, int _actualH, int _worldLeft, int _worldRight, int _worldTop, int _worldBottom, double _zoom):
    x(_y), y(_y), w(_w), h(_h), actualW(_actualW), actualH(_actualH), worldLeft(_worldLeft), worldRight(_worldRight), worldTop(_worldTop), worldBottom(_worldBottom), zoom(_zoom)
{}

/**
 * @brief Bridge between world coordinates and screen coordinates
 * 
 * @param rect 
 * @return true The rectangle is visible on the screen and should be displayed
 * @return false The rectanlge shouldn't be displayed
 */
bool Camera::transformRect(SDL_Rect* rect) {

    // Should it really be >= or just >

    if(
        // ((rect->x >= x && rect->x <= x+w) || (rect->x + rect->w >= x && rect->x + rect->w <= x+w)) // Horizontal collision
        // && ((rect->y >= y && rect->y <= y+h) || (rect->y + rect->h >= y && rect->y + rect->h <= y+h)) // Vertical collision
        ((rect->x >= x && rect->x <= x+w) || (rect->x + rect->w >= x && rect->x + rect->w <= x+w)) // Horizontal collision
        && ((rect->y >= y && rect->y <= y+h) || (rect->y + rect->h >= y && rect->y + rect->h <= y+h)) // Vertical collision
        // (rect->x >= x && rect->x <= x+w)// Horizontal collision
        // && (rect->y >= y && rect->y <= y+h)// Vertical collision

    ) {
        rect->x = std::round(((double)rect->x - x) * zoom);
        rect->y = std::round(((double)rect->y - y) * zoom);
        rect->w *= zoom;
        rect->h *= zoom;
        return true;
    }
    return false;

}

Point2d<int> Camera::getWorldCoordinates(Point2d<int> input) {
    return Point2d<int>(input.x / zoom + x, input.y / zoom + y);
}

void Camera::setZoom(double _zoom) {

    double oldZoom = zoom;
    int oldW = w;
    int oldH = h;

    zoom = _zoom;
    w = actualW / zoom;
    h = actualH / zoom;

    if(w > worldRight - worldLeft || h > worldBottom - worldTop) {
        zoom = oldZoom;
        w = oldW;
        h = oldH;
        return;
    }

    x += (oldW-w)/2;
    y += (oldH-h)/2;
}

void Camera::move(Vector2d<float> movement) {

    // SDL_Log("Camera position : (%f, %f) + movement to add : (%f, %f) -> (%f, %f)", x, y, movement.x, movement.y, x + movement.x, y + movement.y);

    x += movement.x;
    y += movement.y;

    // x or y can't be less than 0 // FIXME: That should be smoother, right now it blocks brutally
    if(x < worldLeft) {
        x = worldLeft;
    }
    if(y < worldTop) {
        y = worldTop;
    }
    // but can't be more than the world pos either
    if(x >= (worldRight - w)) {
        x = worldRight - w;
    }
    if(y >= (worldBottom - h)) {
        y = worldBottom - h;
    }

    // Maybe if I get rid of double points precision that will work.
    x = std::round(x);
    y = std::round(y);

}