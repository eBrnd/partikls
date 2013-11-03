#ifndef PARTIKL_H
#define PARTIKL_H

#include <cmath>
#include <vector>
#include <SDL/SDL.h>
#include <SDL/SDL_gfxPrimitives.h>

#include <iostream>

class Partikl {
  public:
    enum class Type { PIXEL, CIRCLE, SQUARE };

    Partikl(float _x, float _y, float _vx, float _vy, unsigned int _ttl, unsigned int _size, Type _type, Uint32 _color, float _mass = 0.f, bool _solid = false)
      : x(_x), y(_y), vx(_vx), vy(_vy), ttl(_ttl), size(_size), type(_type), color(_color), mass(_mass), solid(_solid) {}

    inline bool update(const std::vector<Partikl>& partikls) { // returns whether the partikl is still alive after the update
      if(ttl < 0 || ttl--) // negative ttl -> never die.
      {
        x += vx;
        y += vy;

        if(x < 0 || x > 800 || y < 0 || y > 600) // destroy off-screen particles
          return false;

        // gravity based acceleration
        if(mass != 0.f || solid) {
          float ax = 0.f, ay = 0.f;
          for(std::vector<Partikl>::const_iterator it = partikls.begin(); it != partikls.end(); ++it) {
            const float dx = x - it->x;
            const float dy = y - it->y;

            const unsigned int rsquare = dx * dx + dy * dy;

            if(&(*it) != this) {
              if(it->mass != 0.f) {
                if(rsquare == 0)
                  continue;
                const float angle = atan2(dx, dy);

                const float f = it->mass * mass / rsquare;
                const float a = f / mass;

                ax -= std::sin(angle) * a;
                ay -= std::cos(angle) * a;
              }

              if(solid && it->solid && (size + it->size) * (size + it->size) > rsquare) {
                collide(*it);
              }
            }
          }

          vx += ax;
          vy += ay;
        }
        return true;
      }

      return false;
    }

    inline void collide(const Partikl& p) {
      // for testing, just remove particle
      ttl = 0;
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
          vx,vy,
          mass;
    bool solid;
    int ttl;
    unsigned int size;
    Type type; Uint32 color;

};

#endif
