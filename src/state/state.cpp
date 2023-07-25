#include "state/state.hpp"

#include <SDL.h>

#include "SDL_events.h"

void State::handleEvents() {
  SDL_Event* e;
  while (SDL_PollEvent(e)) {
    if (e->type == SDL_QUIT) {
      SDL_Quit();
    } else {
      handleEvent(e);
    }
  }
}