#include "state/menu_state.hpp"

#include <iostream>

#include "common.h"
#include "state/machine.hpp"
#include "state/play_state.hpp"
#include "vector_2d.hpp"

MenuState& MenuState::getInstance(StateMachine& m) {
  static MenuState instance(m);
  return instance;
}

MenuState::MenuState(StateMachine& m)
    : fw(150, 0, 1000, 1000),
      playButton({100, 100}, {100, 30}, "play",
                 [this](const SDL_MouseButtonEvent* e) {
                   machine.changeState(PlayState::getInstance(machine));
                 }),
      machine(m) {}

void MenuState::enter(StateMachine* m) {}
void MenuState::exit(StateMachine* m) {}

void MenuState::render(SDL_Renderer* renderer) {
  fw.render(renderer, [this, renderer]() {
    playButton.drawShape(fw, renderer);
    fw.draw_text({400, 100}, "Tetris 3D", renderer);
  });
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
        playButton.handleClick(reinterpret_cast<SDL_MouseButtonEvent*>(event));
      }
      break;
    }
  }
}

void MenuState::update() {}