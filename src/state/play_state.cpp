#include "state/play_state.hpp"

PlayState& PlayState::getInstance() {
  static PlayState instance;
  return instance;
}

PlayState::PlayState() {}

void PlayState::enter(StateMachine* m) {}
void PlayState::exit(StateMachine* m) {}

void PlayState::render(SDL_Renderer* renderer) {}
void PlayState::handleEvent(SDL_Event* event) {}
void PlayState::update() {}