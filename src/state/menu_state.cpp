#include "state/menu_state.hpp"

MenuState& MenuState::getInstance() {
  static MenuState instance;
  return instance;
}

MenuState::MenuState() {}

void MenuState::enter(StateMachine* m) {}
void MenuState::exit(StateMachine* m) {}

void MenuState::render(SDL_Renderer* renderer) {}
void MenuState::handleEvent(SDL_Event* event) {}
void MenuState::update() {}