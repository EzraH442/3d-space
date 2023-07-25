#include "render/polygon.hpp"

#include "SDL_render.h"
#include "render/drawable_3d.hpp"
#include "render/framework.hpp"

Polygon::Polygon() : Drawable3d(Color::White), vertices() {}

Polygon::~Polygon() {}

Polygon::Polygon(const std::array<Vec3d, 4> vertices, const Color& c)
    : Drawable3d(c), vertices(vertices) {}

Vec3d Polygon::getMidpoint() const {
  Vec3d sum = {0, 0, 0};

  for (auto& v : vertices) {
    sum = sum + v;
  }

  sum = sum / 4;

  return sum;
}
void Polygon::draw(const RenderFramework3d& fw, SDL_Renderer* renderer) const {
  std::array<Vec2d<float>, 4> projected;

  for (int i = 0; i < 4; i++) {
    projected[i] = fw.getProjectedCoordinates(vertices[i]);
  }

  short vx[5];
  short vy[5];

  for (int i = 0; i < 5; i++) {
    vx[i] = (short)projected[i % 4].x;
    vy[i] = (short)projected[i % 4].y;
  }

  filledPolygonRGBA(renderer, vx, vy, projected.size(), color.r, color.g,
                    color.b, color.a);
}