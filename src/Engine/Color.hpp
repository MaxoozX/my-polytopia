/**
 * The file containg the Color class declaration
 * @file Color.hpp
 * @author Maxence
 * @version 1.0
*/

#ifndef COLOR_H
#define COLOR_H

#include <SDL2/SDL.h>

/** A simple class for RGBA color */
class Color {
  
  private:
    int m_red;
    int m_green;
    int m_blue;
    float m_alpha;
  
  public:
    Color(int red = 0, int green = 0, int blue = 0, float alpha = 1.0);
    int getRed() const;
    int getGreen() const;
    int getBlue() const;
    int getAlpha() const;
    void setRendererDrawColor(SDL_Renderer* renderer) const;
  
};

#endif // COLOR_H