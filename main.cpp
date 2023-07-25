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

Framework fw(150, 0, 1000, 1000);

void process_event(SDL_Event *event) {}

void process_input() {}
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
