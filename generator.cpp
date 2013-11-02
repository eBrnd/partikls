#include "generator.h"

#include <cmath>
#include <ctime>

#include "partikl.h"

void Generator::rainbowSplash(Partikls& p, const unsigned int x, const unsigned int y) {
  for(unsigned int i = 0; i < 350; i++) {
    float speed = .5f * (float)h.rand() / (float)RAND_MAX + .5;
    float angle = ((float)h.rand() / (float)RAND_MAX) * 360;
    p.add(Partikl(x, y, (float)cos(angle * (3.14159265 / 180)) * speed, (float)sin(angle * (3.14159265 / 180)) * speed, h.rand() % 64, 2, Partikl::Type::SQUARE, h.hue2rgb(angle + 60)));
  }
}

void Generator::sparks(Partikls &p, const unsigned int x, const unsigned int y) {
  for(unsigned int i = 0; i < 25; i++)
  {
    float speed = (float)h.rand() / (float)RAND_MAX;
    float angle = ((float)h.rand() / (float)RAND_MAX) * 360; // TODO radian conversion can be done right here
    p.add(Partikl(x, y, (float)cos(angle * (3.14159265 / 180)) * speed, (float)sin(angle * (3.14159265 / 180)) * speed + .3f, h.rand() % 100, 1, Partikl::Type::PIXEL, (h.rand() | 0xFF0000FF) & 0xFFD700FF));
  }
}

void Generator::asplode(Partikls& p, const unsigned int x, const unsigned int y) {
  for(unsigned int i = 0; i < 80 * std::pow(2,2 /* hitDuringCombo */); i++)
  {
    float speed = 2 /*hitDuringCombo*/* (float)h.rand() / (float)RAND_MAX; // TODO hitDuringCombo here can be customized
    float angle = ((float)h.rand() / (float)RAND_MAX) * 360;
    p.add(Partikl(x, y, (float)cos(angle * (3.14159265 / 180)) * speed, (float)sin(angle * (3.14159265 / 180)) * speed, h.rand() % 100, 6, Partikl::Type::SQUARE, (h.rand() | 0xFF0000FF) & 0xFFAF3FFF));
  }
}
