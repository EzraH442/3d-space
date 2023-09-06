#include "state/end_state.hpp"

#include <string>

#include "common.h"
#include "state/machine.hpp"
#include "state/menu_state.hpp"
#include "state/play_state.hpp"
#include "vector_2d.hpp"

EndState& EndState::getInstance(StateMachine& m) {
  static EndState instance(m);
  return instance;
}

EndState::EndState(StateMachine& m)
    : fw(150, 0, 1000, 1000),
      playAgainButton({100, 150}, {100, 30}, "Play again",
                      [this](const SDL_MouseButtonEvent* e) {
                        machine.changeState(PlayState::getInstance(machine));
                      }),
      menuButton({100, 200}, {100, 30}, "Main menu",
                 [this](const SDL_MouseButtonEvent* e) {
                   machine.changeState(MenuState::getInstance(machine));
                 }),
      machine(m) {}

void EndState::enter(StateMachine* m) { endScore = m->score; }
void EndState::exit(StateMachine* m) {}

void EndState::render(SDL_Renderer* renderer) {
  fw.render(renderer, [this, renderer]() {
    fw.draw_text({100, 100}, "FINAL SCORE: " + std::to_string(endScore),
                 renderer);
    playAgainButton.drawShape(fw, renderer);
    menuButton.drawShape(fw, renderer);
  });
}

void EndState::handleEvent(SDL_Event* event) {
  switch (event->type) {
    case SDL_KEYDOWN: {
      break;
    }
    case SDL_MOUSEBUTTONDOWN: {
      if (event->button.button == SDL_BUTTON_LEFT) {
        playAgainButton.handleClick(
            reinterpret_cast<SDL_MouseButtonEvent*>(event));
        menuButton.handleClick(reinterpret_cast<SDL_MouseButtonEvent*>(event));
      }
      break;
    }
  }
}

void EndState::update() {}