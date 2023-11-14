#include "state/machine.hpp"

#include "state/end_state.hpp"
#include "state/menu_state.hpp"
#include "state/play_state.hpp"

StateMachine::StateMachine() { current = &MenuState::getInstance(*this); }
StateMachine::~StateMachine() {
  if (current) delete current;
  if (next) delete next;
}

void StateMachine::changeState(State& state) {
  current->exit(this);
  current = &state;
  current->enter(this);
}

void StateMachine::render(Context* context) { current->render(context); }
void StateMachine::handleEvents() { current->handleEvents(*this); }
void StateMachine::update() { current->update(); }