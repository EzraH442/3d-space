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
#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

void main_loop() {}

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
