#ifndef PARTIKL_H
#define PARTIKL_H

#include <SDL/SDL.h>
#include <SDL/SDL_gfxPrimitives.h>

class Partikl {
  public:
    enum class Type { PIXEL, CIRCLE, SQUARE };

    Partikl(float _x, float _y, float _vx, float _vy, unsigned int _ttl, unsigned int _size, Type _type, Uint32 _color)
      : x(_x), y(_y), vx(_vx), vy(_vy), ttl(_ttl), size(_size), type(_type), color(_color) {}

    inline bool update() { // returns whether the partikl is still alive after the update
      if(ttl--)
      {
        x += vx;
        y += vy;
        return true;
      } else {
        return false;
      }
    }

    inline void draw(SDL_Surface* display) {
      switch(type)
      {
        case Type::PIXEL:
          pixelColor(display, (int)x, (int)y, color);
          break;
        case Type::CIRCLE:
          circleColor(display, (int)x, (int)y, size, color);
          break;
        case Type::SQUARE:
          fillRect(display, x, y, size, size, color >> 8);
          break;
      }
    }

  private:
    inline void fillRect(SDL_Surface* display, Sint16 x, Sint16 y, Uint16 w, Uint16 h, Uint32 color) {
      SDL_Rect rect = {x,y,w,h};
      SDL_FillRect(display, &rect, color);
    }

    float x,y,
          vx,vy;
    unsigned int ttl, size;
    Type type; Uint32 color;

};

#endif
