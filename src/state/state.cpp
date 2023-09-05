#include "state/state.hpp"

#include <iostream>

void State::handleEvents() {
  SDL_Event e{};

  std::cout << "handle events\n";
  while (SDL_PollEvent(&e)) {
    std::cout << "poll event\n";
    std::cout << "pointer e " << &e << '\n';
    try {
      std::cout << e.type << " is type \n";
    } catch (...) {
      std::cout << "error handling events\n";
    }
    std::cout << "if\n";
    if (e.type == SDL_QUIT) {
      SDL_Quit();
    } else {
      std::cout << "else\n";
      handleEvent(&e);
    }
  }
}