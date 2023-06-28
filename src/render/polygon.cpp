#include "render/polygon.hpp"

#include "render/framework.hpp"

Polygon::Polygon() : Drawable(Color::White), vertices() {}

Polygon::~Polygon() {}

Polygon::Polygon(const std::array<Vec3d, 4> vertices, const Color& c)
    : Drawable(c), vertices(vertices) {}

Vec3d Polygon::getMidpoint() const {
  Vec3d sum = {0, 0, 0};

  for (auto& v : vertices) {
    sum = sum + v;
  }

  sum = sum / 4;

  return sum;
}
void Polygon::draw(const Framework* fw) const {
  std::array<Vec2d<float>, 4> projected;

  for (int i = 0; i < 4; i++) {
    projected[i] = fw->getProjectedCoordinates(vertices[i]);
  }

  short vx[5];
  short vy[5];

  for (int i = 0; i < 5; i++) {
    vx[i] = (short)projected[i % 4].x;
    vy[i] = (short)projected[i % 4].y;
  }

  filledPolygonRGBA(fw->renderer, vx, vy, projected.size(), color.r, color.g,
                    color.b, color.a);
}