#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

#include <SDL.h>
#include <SDL_events.h>
#include <SDL_keycode.h>
#include <SDL_render.h>
#include <SDL_video.h>

#include "vector_3d.hpp"
#include "render/line.hpp"
#include "render/cube.hpp"
#include "render/camera.hpp"
#include "board/board.hpp"

class Framework {
  int height;
  int width;

public:
  Framework(int height_, int width_): height(height_), width(width_) {
    SDL_Init(SDL_INIT_VIDEO);
    window = SDL_CreateWindow("window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, 0, SDL_RENDERER_ACCELERATED);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
  }

  ~Framework() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
  }

  void draw_square(int x, int y, int w, int h) {
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

    for (int i = x; i < w+x; i++) {
      for (int j = y; j < y+h; j++) {
        SDL_RenderDrawPoint(renderer, i, j);
      }
    }

    SDL_RenderPresent(renderer);
  }

  void draw_cube(Cube c, Camera &camera, int direction) {
    for (Line l : c.toLines()) {
      draw_line(l, camera, direction);
    }
  }

  void draw_line(Line &l, Camera &c, int direction) {
    float d = 500.f;
    Vec3d cameraPos = c.getPos(direction);
    int offset = c.getOffset();

    Vec3d startTransformed = l.start - cameraPos;
    Vec3d endTransformed = l.end - cameraPos;

    // std::cout << "line from " << startTransformed << " to " << endTransformed;

    float scaleStart = d / startTransformed.z;
    float scaleEnd = d / endTransformed.z;

    float x1 = startTransformed.x * scaleStart + 300;
    float y1 = startTransformed.y * scaleStart + 300;

    float x2 = endTransformed.x * scaleEnd + 300;
    float y2 = endTransformed.y * scaleEnd + 300;

    // std::cout << " projected to (" << x1 << ", " << y1 << ") -->" << "(" << x2 << ", " << y2 << ")" << "\n";

    int offsetX;
    int offsetY;

    if (direction == 0) {
      offsetX = -offset * 2;
      offsetY = -offset * 2;
    }
    else if (direction == 1) {
      offsetX = offset * 2;
      offsetY = -offset * 2;
    }
    else if (direction == 2) {
      offsetX = offset * 2;
      offsetY = offset * 2;
    }
    else if (direction == 3) {
      offsetX = -offset * 2;
      offsetY = offset * 2;
    }
    else {
      offsetX = -offset * 2;
      offsetY = -offset * 2;
    }

    SDL_RenderDrawLine(renderer, x1 + offsetX, y1 + offsetY, x2 + offsetX, y2 + offsetY);
  }

  SDL_Renderer *renderer = NULL;
  SDL_Window *window = NULL;
private:
};

Framework fw(800, 800);

std::unordered_map<int, bool> keys;
std::unordered_map<int, bool> mouse;
Camera c;
std::vector<Line> lines;
int cameraPos = 0;

Color white = Color();
Color black = Color(0,0,0);

Cube cube(Vec3d({0,0,0}), white, black);

void process_event(SDL_Event *event) {
  switch(event->type) {
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
      }
      else if (key == SDLK_LEFT || key == SDLK_a) {
        cameraPos = (cameraPos + 3) % 4;
      }
      break;
    }

    case SDL_MOUSEWHEEL: {
      if (event->wheel.y > 0) {
        c.changeHeight(1);
      }
      else if (event->wheel.y < 0) {
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

  SDL_SetRenderDrawColor(fw.renderer, 0, 0, 0, 0);
  SDL_RenderClear(fw.renderer);

  SDL_SetRenderDrawColor(fw.renderer, 255, 255, 255, 255);

  for (int i = 0; i < lines.size(); i++) {
    fw.draw_line(lines[i], c, cameraPos);
  }

  fw.draw_cube(cube, c, cameraPos);

  SDL_RenderPresent(fw.renderer);
}

int main() {

  for (int i = 0; i < 11; i++) {
    lines.push_back(Line({0,i*10,0}, {100,i*10,0}));
  }

  for (int i = 0; i < 11; i++) {
    lines.push_back(Line({i*10, 0 ,0}, {i*10, 100, 0}));
  }

  int boardHeight = 200;
  lines.push_back(Line({0,0,0}, {0,0,boardHeight}));
  lines.push_back(Line({100,0,0}, {100,0,boardHeight}));
  lines.push_back(Line({0,100,0}, {0,100,boardHeight}));
  lines.push_back(Line({100,100,0}, {100,100,boardHeight}));

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
