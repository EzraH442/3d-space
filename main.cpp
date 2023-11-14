#include <SDL.h>
#include <SDL_events.h>
#include <SDL_keycode.h>
#include <SDL_render.h>
#include <SDL_timer.h>
#include <SDL_video.h>

#include <ctime>
#include <iostream>
#include <unordered_map>

#include "color.hpp"
#include "common.h"
#include "state/machine.hpp"
#include "state/state.hpp"

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

float fps = 0;
Uint32 start_time, frame_time;

struct main_loop_data_t {
  StateMachine& m;
};

void main_loop(void* d) {
  main_loop_data_t* data = reinterpret_cast<main_loop_data_t*>(d);
  frame_time = SDL_GetTicks() - start_time;
  start_time = SDL_GetTicks();
  fps = (frame_time > 0) ? 1000.0f / frame_time : 0.0f;
  data->m.handleEvents();
  data->m.update();
  data->m.render(&data->m.ctx);
}

int main() {
  const int width = 1000;
  const int height = 1000;
  srand(time(NULL));

  SDL_Init(SDL_INIT_VIDEO);
  SDL_Window* window = SDL_CreateWindow("window", SDL_WINDOWPOS_UNDEFINED,
                                        SDL_WINDOWPOS_UNDEFINED, width, height,
                                        SDL_WINDOW_SHOWN);

  StateMachine machine;

  main_loop_data_t data = {machine};

  start_time = SDL_GetTicks();
#ifdef __EMSCRIPTEN__
  void* d = &data;
  emscripten_set_main_loop_arg(main_loop, d, 0, 1);
#else

  while (1) {
    // do stuff
    SDL_Delay(15);
    main_loop(&data);
  }
#endif

  return 0;
}
