#include "state/menu_state.hpp"

#include <iostream>

#include "SDL_events.h"
#include "SDL_mouse.h"
#include "vector_2d.hpp"

MenuState& MenuState::getInstance() {
  static MenuState instance;
  return instance;
}

MenuState::MenuState() : fw(150, 0, 1000, 1000) {}

void MenuState::enter(StateMachine* m) {}
void MenuState::exit(StateMachine* m) {}

void MenuState::render(SDL_Renderer* renderer) {
  fw.render(renderer, []() {});
}

void MenuState::handleEvent(SDL_Event* event) {
  switch (event->type) {
    case SDL_KEYDOWN: {
      break;
    }
    case SDL_MOUSEBUTTONDOWN: {
      if (event->button.button == SDL_BUTTON_LEFT) {
        const Vec2d<int> pos{event->button.x, event->button.y};
        // handle button press
        std::cout << pos << '\n';
      }
      break;
    }
  }
}

void MenuState::update() {}