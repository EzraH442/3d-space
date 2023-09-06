#include "state/play_state.hpp"

#include <string>

#include "state/machine.hpp"

PlayState& PlayState::getInstance(StateMachine& m) {
  static PlayState instance(m);
  return instance;
}

PlayState::PlayState(StateMachine& m) : machine(m), fw(150, 0, 1000, 1000) {
  b.init();
  g.init();
}

void PlayState::enter(StateMachine* m) {
  m->score = 0;
  b.clear();
  keys.clear();
  g.reset();
}

void PlayState::exit(StateMachine* m) {}

void PlayState::render(SDL_Renderer* renderer) {
  fw.render(renderer, [this, renderer]() {
    fw.addBoard(b, renderer);
    fw.addTetrisPiece(g.getCurrentPiece(), g.getCurrentPiecePos());
    fw.draw_text_2d({800, 800}, "score: " + std::to_string(g.getScore()),
                    renderer);
  });
}

void PlayState::handleEvent(SDL_Event* event) {
  switch (event->type) {
    case SDL_KEYDOWN: {
      keys[event->key.keysym.sym] = true;
      break;
    }

    case SDL_KEYUP: {
      int key = event->key.keysym.sym;

      keys[event->key.keysym.sym] = false;

      // piece rotations
      if (key == SDLK_w) {
        g.tryRotate({0, 0, -1}, b);
      } else if (key == SDLK_x) {
        g.tryRotate({0, 0, 1}, b);
      } else if (key == SDLK_a) {
        g.tryRotate({0, -1, 0}, b);
      } else if (key == SDLK_d) {
        g.tryRotate({0, 1, 0}, b);
      } else if (key == SDLK_z) {
        g.tryRotate({-1, 0, 0}, b);
      } else if (key == SDLK_e) {
        g.tryRotate({1, 0, 0}, b);
      }

      // piece movement
      else if (key == SDLK_i) {
        g.tryMove({0, 1, 0}, b);
      } else if (key == SDLK_j) {
        g.tryMove({1, 0, 0}, b);
      } else if (key == SDLK_k) {
        g.tryMove({0, -1, 0}, b);
      } else if (key == SDLK_l) {
        g.tryMove({-1, 0, 0}, b);
      }

      // hard drop
      else if (key == SDLK_s) {
        g.hardDrop(b, machine);
      }
      break;
    }

    case SDL_MOUSEWHEEL: {
      if (event->wheel.y > 0) {
        fw.c.move({0, 0, 1});
      } else if (event->wheel.y < 0) {
        fw.c.move({0, 0, -1});
      }
      break;
    }
  }
}

void PlayState::update() {
  if (SDL_GetTicks() % 30 == 0) {
    bool moved = g.tryMove({0, 0, -1}, b);
    if (!moved) g.hardDrop(b, machine);
  }

  if (keys[SDLK_UP]) {
    fw.c.move({0, 1, 0});
  }
  if (keys[SDLK_DOWN]) {
    fw.c.move({0, -1, 0});
  }
  if (keys[SDLK_LEFT]) {
    fw.c.move({1, 0, 0});
  }
  if (keys[SDLK_RIGHT]) {
    fw.c.move({-1, 0, 0});
  }
  if (keys[SDLK_o]) {
    bool moved = g.tryMove({0, 0, -1}, b);
    if (!moved) g.hardDrop(b, machine);
  }
}