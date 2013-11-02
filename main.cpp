#include <iostream>
#include <SDL/SDL.h>
#include <SDL/SDL_framerate.h>

#include "partikls.h"
#include "generator.h"

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
  Generator g;

  for(;;) {
    // handle input
    SDL_Event event;
    while(SDL_PollEvent(&event)) {
      switch(event.type) {
        case SDL_MOUSEBUTTONDOWN:
          switch(event.button.button) {
            case 1:
              g.rainbowSplash(partikls, event.button.x, event.button.y);
              break;
            case 3:
              g.asplode(partikls, event.button.x, event.button.y);
              break;
          }
          break;
        case SDL_MOUSEMOTION:
          g.sparks(partikls, event.motion.x, event.motion.y);
          break;
        case SDL_KEYDOWN:
          switch(event.key.keysym.sym)
          {
            case SDLK_ESCAPE:
              SDL_Quit();
              exit(0);
          }
          break;
      }
    }


    // draw the scene
    SDL_FillRect(display, NULL, 0); // clear the buffer

    partikls.update();
    partikls.draw(display);

    SDL_Flip(display);

    SDL_framerateDelay(fpsmanager);
  }
}
