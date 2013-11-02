#ifndef GENERATOR_H
#define GENERATOR_H

#include "partikls.h"
#include "generatorHelper.h"

class Generator {
  public:
    void rainbowSplash(Partikls& p, const unsigned int x, const unsigned int y);
    void sparks(Partikls &p, const unsigned int x, const unsigned int y);

  private:
    GeneratorHelper h;
};

#endif
