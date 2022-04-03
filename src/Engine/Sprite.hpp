/**
 * Implementation file for Sprite class.
 * @file Sprite.cpp
 * @author Maxence
 * @version 1.0
*/

#ifndef SPRITE_H
#define SPRITE_H

#include <SDL2/SDL.h>
#include "Geometry.hpp"

/**
 * The Sprite class
*/
class Sprite {
  /*
  The class needs to have a corresponding rectangle, polygon, and texture, with some internal state.
  */
  
  public:
    Geometry::Point2d<double> center;
    int m_width;
    int m_height;
    int m_pixelSize;
    SDL_Rect m_rect;
    Geometry::Polygon<int> shapePolygon, scaledPolygon, displayPolygon;
    SDL_Texture* m_texture;
    SDL_Renderer* m_renderer;
    
    // Methods
    Sprite(float = 0, float = 0, int = 0, int = 0, SDL_Renderer* = nullptr, int = 0);
    Sprite(const Sprite &);
    ~Sprite();
    
    void loadPolygons(const char[]);
    
    void loadTexture(const char[]);

    void load(const char[], const char[]);

    void positionDisplayPolygon(int = 0, int = 0);

    void setRenderer(SDL_Renderer*);

    void setTexture(SDL_Texture*);

    void setScaledPolygon(Geometry::Polygon<int> &);

    static bool doesRectanglesCollide(SDL_Rect &rect1, SDL_Rect &rect2);
    
};

#endif // SPRITE_H