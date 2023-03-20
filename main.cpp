#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

#include <SDL.h>
#include <SDL_events.h>
#include <SDL_keycode.h>
#include <SDL_render.h>
#include <SDL_video.h>

#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

#include "board/board.hpp"
#include "color.hpp"
#include "render/camera.hpp"
#include "render/cube.hpp"
#include "render/line.hpp"
#include "vector_3d.hpp"

class Framework {
  int height;
  int width;

 public:
  Framework(int height_, int width_) : height(height_), width(width_) {
    SDL_Init(SDL_INIT_VIDEO);
    window = SDL_CreateWindow("window", SDL_WINDOWPOS_UNDEFINED,
                              SDL_WINDOWPOS_UNDEFINED, width, height,
                              SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, 0, SDL_RENDERER_ACCELERATED);
    SDL_SetRenderDrawColor(renderer, Color::Black.r, Color::Black.g,
                           Color::Black.b, Color::Black.a);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
  }

  ~Framework() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
  }

  void draw_board(Board &b, Camera &camera, int direction) {
    for (const auto &l : b.getLines()) {
      draw_line(l, camera, direction);
    }

    for (auto const &pair : b.getCubes()) {
      draw_cube(pair.second, camera, direction);
    }
  }

  void draw_cube(const Cube &c, const Camera &camera, int direction) {
    for (const Line &l : c.toLines()) {
      draw_line(l, camera, direction);
    }

    // TODO draw cube faces
  }

  void draw_line(const Line &l, const Camera &c, int direction) {
    float d = 500.f;
    Vec3d cameraPos = c.getPos(direction);
    int offset = c.getOffset();

    Vec3d startTransformed = l.start - cameraPos;
    Vec3d endTransformed = l.end - cameraPos;

    // std::cout << "line from " << startTransformed << " to " <<
    // endTransformed;

    float scaleStart = d / startTransformed.z;
    float scaleEnd = d / endTransformed.z;

    float x1 = startTransformed.x * scaleStart + 300;
    float y1 = startTransformed.y * scaleStart + 300;

    float x2 = endTransformed.x * scaleEnd + 300;
    float y2 = endTransformed.y * scaleEnd + 300;

    // std::cout << " projected to (" << x1 << ", " << y1 << ") -->" << "(" <<
    // x2 << ", " << y2 << ")" << "\n";

    int offsetX;
    int offsetY;

    if (direction == 0) {
      offsetX = -offset * 2;
      offsetY = -offset * 2;
    } else if (direction == 1) {
      offsetX = offset * 2;
      offsetY = -offset * 2;
    } else if (direction == 2) {
      offsetX = offset * 2;
      offsetY = offset * 2;
    } else if (direction == 3) {
      offsetX = -offset * 2;
      offsetY = offset * 2;
    } else {
      offsetX = -offset * 2;
      offsetY = -offset * 2;
    }

    SDL_SetRenderDrawColor(renderer, l.color.r, l.color.g, l.color.b,
                           l.color.a);
    SDL_RenderDrawLine(renderer, x1 + offsetX, y1 + offsetY, x2 + offsetX,
                       y2 + offsetY);
  }

  SDL_Renderer *renderer = NULL;
  SDL_Window *window = NULL;

 private:
};

Framework fw(800, 800);

std::unordered_map<int, bool> keys;
std::unordered_map<int, bool> mouse;
Camera c;
int cameraPos = 0;

Board b;

Cube cube(Vec3d({0, 0, 0}), Color::White, Color::Black);
Cube cube2(Vec3d({1, 0, 0}), Color::White, Color::Black);
Cube cube3(Vec3d({2, 0, 0}), Color::White, Color::Black);
Cube cube4(Vec3d({3, 0, 0}), Color::White, Color::Black);

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
      if (key == SDLK_RIGHT || key == SDLK_d) {
        cameraPos = (cameraPos + 1) % 4;
      } else if (key == SDLK_LEFT || key == SDLK_a) {
        cameraPos = (cameraPos + 3) % 4;
      }
      break;
    }

    case SDL_MOUSEWHEEL: {
      if (event->wheel.y > 0) {
        c.changeHeight(1);
      } else if (event->wheel.y < 0) {
        c.changeHeight(-1);
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

  if (keys[SDLK_UP] || keys[SDLK_w]) {
    c.changeOffset(1);
  }
  if (keys[SDLK_DOWN] || keys[SDLK_s]) {
    c.changeOffset(-1);
  }
}

void main_loop() {
  process_input();

  SDL_SetRenderDrawColor(fw.renderer, Color::Black.r, Color::Black.g,
                         Color::Black.b, Color::Black.a);
  SDL_RenderClear(fw.renderer);

  fw.draw_board(b, c, cameraPos);

  SDL_RenderPresent(fw.renderer);
}

int main() {
  b.addCube(0, 0, 0, cube);
  b.addCube(1, 0, 0, cube2);
  b.addCube(2, 0, 0, cube3);
  b.addCube(3, 0, 0, cube4);
#ifdef __EMSCRIPTEN__
  emscripten_set_main_loop(main_loop, 0, 1);
#else
  while (1) {
    SDL_Delay(50);
    main_loop();
  }
#endif

  return 0;
}
