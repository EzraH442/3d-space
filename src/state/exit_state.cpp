#include "state/exit_state.hpp"

#include <cstdlib>

#include "common.h"
#include "state/machine.hpp"
#include "vector_2d.hpp"

ExitState& ExitState::getInstance(StateMachine& m) {
  static ExitState instance(m);
  return instance;
}

ExitState::ExitState(StateMachine& m) : machine(m) {}

void ExitState::enter(StateMachine* m) {
  SDL_Quit();
  ::exit(0);
}
void ExitState::exit(StateMachine* m) {}

void ExitState::render(Context* context) {}

void ExitState::handleEvent(SDL_Event* event) {}

void ExitState::update() {}