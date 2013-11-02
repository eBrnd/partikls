#ifndef GENERATOR_H
#define GENERATOR_H

#include "partikls.h"
#include <boost/random.hpp>

class Generator {
  public:
    Generator();

    void rainbowSplash(Partikls& p, const unsigned int x, const unsigned int y);

  private:

    // random number generator fun
    unsigned int rand();
    boost::mt19937* rng;

    Uint32 hue2rgb(float h);
};

#endif
