#include <iostream>
#include <SDL/SDL.h>
#include <SDL/SDL_framerate.h>

#include "partikls.h"

int main() {
  if (SDL_Init(SDL_INIT_VIDEO) < 0)
  {
    std::cout << "Could not initialize SDL: " << SDL_GetError() << std::endl;
    exit(1);
  }

  int sdlopts = SDL_SWSURFACE | SDL_DOUBLEBUF;

  int colordepth = 32;

  SDL_Surface *display;
  display = SDL_SetVideoMode(800, 600, colordepth, sdlopts); // HWSURFACE?
  if(display == NULL)
  {
    std::cout << "Could not initialize video: " << SDL_GetError() << std::endl;
    exit(1);
  }

  atexit(SDL_Quit);

  FPSmanager* fpsmanager = new FPSmanager();
  SDL_initFramerate(fpsmanager);
  SDL_setFramerate(fpsmanager, 60);

  Partikls partikls;
  partikls.add(Partikl(100, 100, 1, 1, 100, 5, Partikl::Type::SQUARE, 0xffffffff));

  for(;;) {
    SDL_FillRect(display, NULL, 0); // clear the buffer

    partikls.update();
    partikls.draw(display);

    SDL_Flip(display);

    SDL_framerateDelay(fpsmanager);
  }
}
