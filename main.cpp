#include <unordered_map>

#include "SDL_timer.h"
#include "game.hpp"
#include "render/framework.hpp"
#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

#include <SDL.h>
#include <SDL2_gfxPrimitives.h>
#include <SDL_events.h>
#include <SDL_keycode.h>
#include <SDL_render.h>
#include <SDL_video.h>

std::unordered_map<int, bool> keys;
std::unordered_map<int, bool> mouse;

Framework fw(800, 1000);
Board b;
Game g;

void process_event(SDL_Event *event) {
  switch (event->type) {
    case SDL_QUIT:
      SDL_Quit();

      break;

    case SDL_KEYDOWN: {
      keys[event->key.keysym.sym] = true;
      break;
    }

    case SDL_KEYUP: {
      int key = event->key.keysym.sym;

      keys[event->key.keysym.sym] = false;

      // camera
      // if (key == SDLK_RIGHT) {
      //   cameraPos = (cameraPos + 1) % 4;
      // } else if (key == SDLK_LEFT) {
      //   cameraPos = (cameraPos + 3) % 4;
      // }

      // piece rotations
      if (key == SDLK_w) {
        g.tryRotate({0, 0, 1}, b);
      } else if (key == SDLK_x) {
        g.tryRotate({0, 0, -1}, b);
      } else if (key == SDLK_a) {
        g.tryRotate({0, 1, 0}, b);
      } else if (key == SDLK_d) {
        g.tryRotate({0, -1, 0}, b);
      } else if (key == SDLK_z) {
        g.tryRotate({1, 0, 0}, b);
      } else if (key == SDLK_e) {
        g.tryRotate({-1, 0, 0}, b);
      }

      // piece movement
      else if (key == SDLK_i) {
        g.tryMove({0, -1, 0}, b);
      } else if (key == SDLK_j) {
        g.tryMove({-1, 0, 0}, b);
      } else if (key == SDLK_k) {
        g.tryMove({0, 1, 0}, b);
      } else if (key == SDLK_l) {
        g.tryMove({1, 0, 0}, b);
      }

      // hard drop
      else if (key == SDLK_s) {
        g.hardDrop(b);
      }
      break;
    }

    case SDL_MOUSEWHEEL: {
      if (event->wheel.y > 0) {
        fw.moveCamera({0, 0, 1});
      } else if (event->wheel.y < 0) {
        fw.moveCamera({0, 0, -1});
      }
      break;
    }
  }
}

void process_input() {
  SDL_Event event;

  while (SDL_PollEvent(&event)) {
    process_event(&event);
  }

  if (keys[SDLK_UP]) {
    fw.moveCamera({0, 1, 0});
  }
  if (keys[SDLK_DOWN]) {
    fw.moveCamera({0, -1, 0});
  }
  if (keys[SDLK_LEFT]) {
    fw.moveCamera({1, 0, 0});
  }
  if (keys[SDLK_RIGHT]) {
    fw.moveCamera({-1, 0, 0});
  }
  if (keys[SDLK_o]) {
    bool moved = g.tryMove({0, 0, -1}, b);
    if (!moved) g.hardDrop(b);
  }
}
void main_loop() {
  process_input();

  fw.clear();
  fw.addBoard(b);
  fw.addTetrisPiece(g.getCurrentPiece(), g.getCurrentPiecePos());

  fw.display();
}

int main() {
  srand(time(NULL));

  b.init();
  g.init();
#ifdef __EMSCRIPTEN__
  emscripten_set_main_loop(main_loop, 0, 1);
#else

  while (1) {
    SDL_Delay(20);
    main_loop();
  }
#endif

  return 0;
}
