#include "generator.h"

#include <cmath>
#include <ctime>

#include "partikl.h"

void Generator::rainbowSplash(Partikls& p, const unsigned int x, const unsigned int y) {
  for(int i = 0; i < 350; i++) {
    float speed = .5f * (float)h.rand() / (float)RAND_MAX + .5;
    float angle = ((float)h.rand() / (float)RAND_MAX) * 360;
    p.add(Partikl(x, y, (float)cos(angle * (3.14159265 / 180)) * speed, (float)sin(angle * (3.14159265 / 180)) * speed, h.rand() % 64, 2, Partikl::Type::SQUARE, h.hue2rgb(angle + 60)));
  }
}
