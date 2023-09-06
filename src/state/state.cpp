#include "state/state.hpp"

#include "state/exit_state.hpp"
#include "state/machine.hpp"

void State::handleEvents(StateMachine& m) {
  SDL_Event e{};

  while (SDL_PollEvent(&e)) {
    if (e.type == SDL_QUIT) {
      m.changeState(ExitState::getInstance(m));
    } else {
      handleEvent(&e);
    }
  }
}