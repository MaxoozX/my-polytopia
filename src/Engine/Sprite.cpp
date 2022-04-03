/**
 * Header file for Sprite class.
 * @file Sprite.cpp
 * @author Maxence
 * @version 1.0
*/

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "Geometry.hpp"

#include "Sprite.hpp"

using namespace Geometry;

Sprite::Sprite(float x, float y, int width, int height, SDL_Renderer* renderer, int pixelSize):
  center(x, y), m_width(width), m_height(height),
  m_pixelSize(pixelSize), m_renderer(renderer)
  {

      m_rect.x = x - width/2;
      m_rect.y = y - height/2;
      m_rect.w = width;
      m_rect.h = height;
      
    }

Sprite::~Sprite() = default;

void Sprite::loadPolygons(const char path[]) {
  
  shapePolygon = getPolygonFromPNG<int>(path);

  shapePolygon.computeMidPoint();

  // Scale the polygon
  scaledPolygon = Polygon<int>(shapePolygon);
  
  double scaleFactorX = m_width / shapePolygon.m_w;
  double scaleFactorY = m_height / shapePolygon.m_h;
  
  for(auto &vertex : scaledPolygon.vertices) {
    vertex.x *= scaleFactorX;
    vertex.y *= scaleFactorY;
  }
  
  scaledPolygon.m_w = m_width;
  scaledPolygon.m_h = m_height;
  
  double deltaX = center.x - m_width / 2 + m_pixelSize / 2;
  double deltaY = center.y - m_height / 2 + m_pixelSize / 2;

  positionDisplayPolygon(deltaX, deltaY);

}

void Sprite::positionDisplayPolygon(int deltaX, int deltaY) {
  // Position the polygon
  displayPolygon = Polygon<int>(scaledPolygon);
  
  for(auto &vertex : displayPolygon.vertices) {
    vertex.x += deltaX;
    vertex.y += deltaY;
  }
}

void Sprite::loadTexture(const char path[]) {
  SDL_Log("loading texture : %s", path);
  m_texture = IMG_LoadTexture(m_renderer, path);
  if (m_texture == nullptr) {
    SDL_Log("Problem loading sprite texture : %s", IMG_GetError());
  }
}

void Sprite::load(const char shapePath[], const char texturePath[]) {
  loadPolygons(shapePath);
  loadTexture(texturePath);
}

void Sprite::setRenderer(SDL_Renderer* newRenderer) {
    m_renderer = newRenderer;
}

void Sprite::setTexture(SDL_Texture* newTexture) {
  m_texture = newTexture;
}

void Sprite::setScaledPolygon(Geometry::Polygon<int> &poly) {
  scaledPolygon = Polygon<int>(poly);
}

bool Sprite::doesRectanglesCollide(SDL_Rect &rect1, SDL_Rect &rect2) {
  return (!(rect1.x + rect1.w < rect2.x || rect1.x > rect2.x + rect2.w || rect1.y + rect1.h < rect2.y || rect1.y > rect2.y + rect2.h ));
}
