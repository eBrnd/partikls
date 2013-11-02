#ifndef GENERATOR_HELPER_H
#define GENERATOR_HELPER_H

#include <boost/random.hpp>
#include <SDL/SDL.h>

class GeneratorHelper {
  public:
    GeneratorHelper();
    ~GeneratorHelper();

    unsigned int rand();
    Uint32 hue2rgb(float h);

  private:
    boost::mt19937* rng;
};

#endif
