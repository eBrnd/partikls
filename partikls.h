#include "partikl.h"

#include <vector>

class SDL_Surface;

class Partikls {
  private:
    std::vector<Partikl> partikls;

  public:
    Partikls() {}
    ~Partikls() {}

    void add(const Partikl& p);
    void draw(SDL_Surface* display);
    void update();
};
