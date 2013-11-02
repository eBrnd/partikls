#include "generator.h"

#include <cmath>
#include <ctime>

#include "partikl.h"

Generator::Generator() {
  // start up random generator
  rng = new boost::mt19937;
  rng->seed(static_cast<unsigned int>(std::time(NULL)));
}

unsigned int Generator::rand()
{
  boost::uniform_int<> randrange(0, RAND_MAX-1);
  boost::variate_generator< boost::mt19937&, boost::uniform_int<> > random(*rng, randrange);
  return random();
}

Uint32 Generator::hue2rgb(float h)
{
  while(h > 360) h -= 360; // normalize to 360 degrees
  while(h < 0) h += 360;
  h = h / 60;
  float x = 1 - abs(fmod(h, 2)); // see Wikipedia - and in our case, C = 1.
  if(0 <= h && h < 1)
    return 0xFF0000FF | (Uint8)(x * 255) << 16; // r = 255, g = (x*255), b = 0, a = 255
  if(1 <= h && h < 2)
    return 0x00FF00FF | (Uint8)(x * 255) << 24;
  if(2 <= h && h < 3)
    return 0x00FF00FF | (Uint8)(x * 255) << 8;
  if(3 <= h && h < 4)
    return 0x0000FFFF | (Uint8)(x * 255) << 16;
  if(4 <= h && h < 5)
    return 0x0000FFFF | (Uint8)(x * 255) << 24;
  if(5 <= h && h < 6)
    return 0xFF0000FF | (Uint8)(x * 255) << 8;
  return 0;
}

void Generator::rainbowSplash(Partikls& p, const unsigned int x, const unsigned int y) {
  for(int i = 0; i < 350; i++) {
    float speed = .5f * (float)rand() / (float)RAND_MAX + .5;
    float angle = ((float)rand() / (float)RAND_MAX) * 360;
    p.add(Partikl(x, y, (float)cos(angle * (3.14159265 / 180)) * speed, (float)sin(angle * (3.14159265 / 180)) * speed, rand() % 64, 2, Partikl::Type::SQUARE, hue2rgb(angle + 60)));
  }
}
