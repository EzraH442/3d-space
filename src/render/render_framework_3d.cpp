#include "render/render_framework_3d.hpp"

#include <SDL2_gfxPrimitives.h>

#include <algorithm>

#include "render/drawable_3d.hpp"
#include "render/line.hpp"
#include "render/polygon.hpp"

RenderFramework3d::RenderFramework3d(int x, int y, int height, int width)
    : c(100), x(x), y(y), height(height), width(width) {}

void RenderFramework3d::renderObjects(SDL_Renderer *renderer) {
  for (auto &d : baseLayer) {
    d->drawShape(*this, renderer);
  }

  for (auto &layer : toDraw) {
    for (auto &d : layer) {
      d->drawShape(*this, renderer);
    }
  }
}

void RenderFramework3d::clearDrawables() {
  for (auto &layer : toDraw) {
    layer.clear();
  }
}

bool RenderFramework3d::isBackface(const Drawable3d &d) const {
  auto dist = d.getVertex() - c.getPos();
  auto test = dist * d.getNormal();

  return test > 0;
}

void RenderFramework3d::drawDrawables(const std::function<void()> &f) {
  f();

  for (auto &layer : toDraw) {
    std::sort(layer.begin(), layer.end(),
              [this](const std::unique_ptr<Drawable3d> &d1,
                     const std::unique_ptr<Drawable3d> &d2) {
                int dist1 = (d1->getMidpoint() - c.getPos()).squaredMagnitude();
                int dist2 = (d2->getMidpoint() - c.getPos()).squaredMagnitude();

                return dist1 > dist2;
              });
  }
}

Vec2d<float> RenderFramework3d::getProjectedCoordinates(const Vec3d &p) const {
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

void RenderFramework3d::draw_text_3d(const Vec3d &pos, std::string s,
                                     SDL_Renderer *renderer) {
  for (size_t i = 0; i < s.length(); i++) {
    Vec2d<float> projectedPos =
        getProjectedCoordinates(pos + Vec3d{static_cast<int>(i * 10), 0, 0});
    characterRGBA(renderer, projectedPos.x, projectedPos.y, s[i], 255, 255, 255,
                  255);
  }
}

void RenderFramework3d::addCube(const Cube &c) {
  for (const auto &d : c.toPolygons()) {
    if (!isBackface(d)) {
      toDraw[d.getLayer()].push_back(std::make_unique<Polygon>(d));
    }
  }

  for (const auto &d : c.toLines()) {
    if (!isBackface(d)) {
      toDraw[d.getLayer()].push_back(std::make_unique<Polygon>(d));
    }
  }
}

void RenderFramework3d::addBoard(const Board &b, SDL_Renderer *renderer) {
  for (const auto &d : b.getLines()) {
    baseLayer.push_back(std::make_unique<Line>(d));
  }

  for (auto const &pair : b.getCubes()) {
    addCube(pair.second);
  }

  draw_text_3d(Board::sideN, "N", renderer);
  draw_text_3d(Board::sideE, "E", renderer);
  draw_text_3d(Board::sideS, "S", renderer);
  draw_text_3d(Board::sideW, "W", renderer);
}

void RenderFramework3d::addTetrisPiece(const TetrisPiece3d *piece,
                                       const Vec3d &pos) {
  for (const auto &v : piece->getAbsolutePositions(pos)) {
    addCube(Cube(v, piece->getColor(), Color::White));
  }
}