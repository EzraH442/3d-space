#include "render/framework.hpp"

#include <algorithm>
#include <memory>

#include "render/camera.hpp"
#include "render/drawable.hpp"

Vec2d<float> Framework::getProjectedCoordinates(const Vec3d &p) const {
  float d = 500.f;
  Vec3d cameraPos = c.getPos();
  Vec3d startTransformed = p - cameraPos;

  float scale = d / startTransformed.z;

  float x = scale * startTransformed.x;
  float y = scale * startTransformed.y;

  float offset = d / 2;

  x += offset;
  y += offset;

  Vec2d<float> ret{x + this->x, y + this->y};

  return ret;
}

Framework::Framework(int x, int y, int height, int width)
    : x(x), y(y), height(height), width(width), c(100) {
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

Framework::~Framework() {
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();

  toDraw.clear();
}

void Framework::drawShapes() {
  std::sort(toDraw.begin(), toDraw.end(),
            [this](const std::unique_ptr<Drawable> &d1,
                   const std::unique_ptr<Drawable> &d2) {
              int dist1 = (d1->getMidpoint() - c.getPos()).squaredMagnitude();
              int dist2 = (d2->getMidpoint() - c.getPos()).squaredMagnitude();

              return dist1 > dist2;
            });

  for (const auto &d : toDraw) {
    d->drawShape(this);
  }
}

void Framework::moveCamera(const Vec3d &v) { c.move(v); }

void Framework::draw_text_3d(const Vec3d &pos, std::string s) {
  for (int i = 0; i < s.length(); i++) {
    Vec2d<float> projectedPos =
        getProjectedCoordinates(pos + Vec3d{i * 10, 0, 0});
    characterRGBA(renderer, projectedPos.x, projectedPos.y, s[i], 255, 255, 255,
                  255);
  }
}

void Framework::draw_text_2d(const Vec2d<float> &pos, std::string s) {
  for (int i = 0; i < s.length(); i++) {
    characterRGBA(renderer, pos.x, pos.y, s[i], 255, 255, 255, 255);
  }
}

void Framework::addCube(const Cube &c) {
  for (const auto &d : c.toPolygons()) {
    toDraw.push_back(std::make_unique<Polygon>(d));
  }

  for (const auto &d : c.toLines()) {
    toDraw.push_back(std::make_unique<Polygon>(d));
  }
}

void Framework::addBoard(const Board &b) {
  for (const auto &d : b.getLines()) {
    toDraw.push_back(std::make_unique<Line>(d));
  }

  for (auto const &pair : b.getCubes()) {
    addCube(pair.second);
  }

  draw_text_3d(Board::sideN, "N");
  draw_text_3d(Board::sideE, "E");
  draw_text_3d(Board::sideS, "S");
  draw_text_3d(Board::sideW, "W");
}

void Framework::addTetrisPiece(const TetrisPiece3d *piece, const Vec3d &pos) {
  for (const auto &v : piece->getAbsolutePositions(pos)) {
    addCube(Cube(v, piece->getColor(), Color::White));
  }
}

void Framework::clear() {
  SDL_SetRenderDrawColor(renderer, Color::Black.r, Color::Black.g,
                         Color::Black.b, Color::Black.a);
  SDL_RenderClear(renderer);
  toDraw.clear();
}

void Framework::display() {
  drawShapes();
  SDL_RenderPresent(renderer);
}