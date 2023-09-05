#include "state/state.hpp"

void State::handleEvents() {
  SDL_Event e{};

  while (SDL_PollEvent(&e)) {
    if (e.type == SDL_QUIT) {
      SDL_Quit();
    } else {
      handleEvent(&e);
    }
  }
}