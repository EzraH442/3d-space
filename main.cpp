#include <SDL.h>
#include <SDL2_gfxPrimitives.h>
#include <SDL_events.h>
#include <SDL_keycode.h>
#include <SDL_render.h>
#include <SDL_timer.h>
#include <SDL_video.h>

#include <ctime>
#include <unordered_map>

#include "color.hpp"
#include "state/machine.hpp"
#include "state/state.hpp"

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

struct main_loop_data_t {
  StateMachine& m;
  SDL_Renderer* renderer;
};

void main_loop(void* d) {
  main_loop_data_t* data = reinterpret_cast<main_loop_data_t*>(d);
  data->m.handleEvents();
  data->m.update();
  data->m.render(data->renderer);
}

int main() {
  const int width = 1000;
  const int height = 1000;
  srand(time(NULL));

  SDL_Init(SDL_INIT_VIDEO);
  SDL_Window* window = SDL_CreateWindow("window", SDL_WINDOWPOS_UNDEFINED,
                                        SDL_WINDOWPOS_UNDEFINED, width, height,
                                        SDL_WINDOW_SHOWN);
  SDL_Renderer* renderer =
      SDL_CreateRenderer(window, 0, SDL_RENDERER_ACCELERATED);

  SDL_SetRenderDrawColor(renderer, Color::Black.r, Color::Black.g,
                         Color::Black.b, Color::Black.a);
  SDL_RenderClear(renderer);
  SDL_RenderPresent(renderer);

  StateMachine machine;

  main_loop_data_t data = {machine, renderer};

#ifdef __EMSCRIPTEN__
  void* d = &data;
  emscripten_set_main_loop_arg(main_loop, d, 0, 0);
#else

  while (1) {
    SDL_Delay(20);
    main_loop(&data);
  }
#endif

  return 0;
}
