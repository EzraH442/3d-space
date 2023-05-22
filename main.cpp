#include <unordered_map>

#include "game.hpp"
#include "render/camera.hpp"
#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

#include <SDL.h>
#include <SDL2_gfxPrimitives.h>
#include <SDL_events.h>
#include <SDL_keycode.h>
#include <SDL_render.h>
#include <SDL_video.h>

Vec2d<float> project(const Vec3d &p, const Camera &c, int direction) {
  float d = 500.f;
  Vec3d cameraPos = c.getPos(direction);
  Vec3d startTransformed = p - cameraPos;

  float scale = d / startTransformed.z;

  float x = scale * startTransformed.x;
  float y = scale * startTransformed.y;

  // temp variables for rotation
  float rotatedX = x;
  float rotatedY = y;

  // multiply by 2x2 clockwirse rotation matrix
  //  0 -1
  //  1  0
  for (int i = 0; i < direction; i++) {
    rotatedX = -y;
    rotatedY = x;
    x = rotatedX;
    y = rotatedY;
  }

  // reposition all points

  if (direction == 1) {
    x += 250;
  } else if (direction == 2) {
    x += 250;
    y += 250;
  } else if (direction == 3) {
    y += 250;
  }

  Vec2d<float> ret{x, y};

  // std::cout << "point at " << p << " projected to {" << ret.x << ", " <<
  // ret.y
  //           << " }\n";
  return ret;
}

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

  void draw_text(const Vec3d &pos, std::string s, const Camera &camera,
                 int direction) {
    for (int i = 0; i < s.length(); i++) {
      Vec2d<float> projectedPos =
          project(pos + Vec3d{i * 10, 0, 0}, camera, direction);
      characterRGBA(renderer, projectedPos.x + 300, projectedPos.y + 300, s[i],
                    255, 255, 255, 255);
    }
  }

  void draw_tetris_piece(const TetrisPiece3d *piece, const Vec3d &pos,
                         const Camera &camera, int direction) {
    for (const auto &v : piece->getAbsolutePositions(pos)) {
      draw_cube(Cube(v, piece->getColor(), Color::White), camera, direction);
    }
  }

  void draw_board(const Board &b, const Camera &camera, int direction) {
    for (const auto &l : b.getLines()) {
      draw_line(l, camera, direction);
    }

    for (auto const &pair : b.getCubes()) {
      draw_cube(pair.second, camera, direction);
    }

    draw_text(Board::sideN, "N", camera, direction);
    draw_text(Board::sideE, "E", camera, direction);
    draw_text(Board::sideS, "S", camera, direction);
    draw_text(Board::sideW, "W", camera, direction);
  }

  void draw_cube(const Cube &c, const Camera &camera, int direction) {
    std::vector<std::array<Vec3d, 4>> polygons = c.toPolygons();
    for (int i = 0; i < polygons.size(); i++) {
      draw_cube_face(polygons[i], c.getFillColor(), camera, direction);
    }

    for (const Line &l : c.toLines()) {
      draw_line(l, camera, direction);
    }
  }

  void draw_cube_face(const std::array<Vec3d, 4> &points, const Color &color,
                      const Camera &c, int direction) {
    std::array<Vec2d<float>, 4> projected;

    for (int i = 0; i < 4; i++) {
      projected[i] = project(points[i], c, direction);
    }

    short vx[5];
    short vy[5];

    for (int i = 0; i < 5; i++) {
      vx[i] = (short)projected[i % 4].x + 300;
      vy[i] = (short)projected[i % 4].y + 300;
    }

    filledPolygonRGBA(renderer, vx, vy, projected.size(), color.r, color.g,
                      color.b, color.a);
  }

  void draw_line(const Line &l, const Camera &c, int direction) {
    Vec2d<float> start = project(l.start, c, direction);
    Vec2d<float> end = project(l.end, c, direction);

    SDL_SetRenderDrawColor(renderer, l.color.r, l.color.g, l.color.b,
                           l.color.a);
    SDL_RenderDrawLine(renderer, start.x + 300, start.y + 300, end.x + 300,
                       end.y + 300);
  }

  SDL_Renderer *renderer = NULL;
  SDL_Window *window = NULL;

 private:
};

Framework fw(800, 800);
std::unordered_map<int, bool> keys;
std::unordered_map<int, bool> mouse;

Camera c;
int cameraPos = 2;
// int cameraPos = 3;

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
      if (key == SDLK_RIGHT) {
        cameraPos = (cameraPos + 1) % 4;
      } else if (key == SDLK_LEFT) {
        cameraPos = (cameraPos + 3) % 4;
      }

      // piece rotations
      else if (key == SDLK_w) {
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

      // soft and hard drop
      else if (key == SDLK_s) {
        g.hardDrop(b);
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

  if (keys[SDLK_UP]) {
    c.changeOffset(1);
  }
  if (keys[SDLK_DOWN]) {
    c.changeOffset(-1);
  }
  if (keys[SDLK_o]) {
    g.tryMove({0, 0, -1}, b);
  }
}

void main_loop() {
  process_input();

  SDL_SetRenderDrawColor(fw.renderer, Color::Black.r, Color::Black.g,
                         Color::Black.b, Color::Black.a);
  SDL_RenderClear(fw.renderer);

  fw.draw_board(b, c, cameraPos);

  fw.draw_tetris_piece(g.getCurrentPiece(), g.getCurrentPiecePos(), c,
                       cameraPos);

  SDL_RenderPresent(fw.renderer);
}

int main() {
  srand(time(NULL));
#ifdef __EMSCRIPTEN__
  emscripten_set_main_loop(main_loop, 0, 1);
#else

  b.init();
  g.init();

  while (1) {
    SDL_Delay(20);
    main_loop();
  }
#endif

  return 0;
}
