#include "render/polygon.hpp"

#include "render/render_framework_3d.hpp"
#include "vector_3d.hpp"

Polygon::Polygon() : Drawable3d(Color::White), vertices(), layer(0) {}

Polygon::~Polygon() {}

Polygon::Polygon(const std::array<Vec3d, 4> vertices, const Color& c, int layer)
    : Drawable3d(c), vertices(vertices), layer(layer) {}

Vec3d Polygon::getMidpoint() const {
  Vec3d sum = {0, 0, 0};

  for (auto& v : vertices) {
    sum = sum + v;
  }

  sum = sum / 4;

  return sum;
}

void Polygon::draw(const RenderFramework3d& fw, Context* context) const {
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

  // filledPolygonRGBA(context, vx, vy, projected.size(), color.r, color.g,
  //                   color.b, color.a);
}

Vec3d Polygon::getNormal() const {
  return (vertices[0] - vertices[1]) ^ (vertices[2] - vertices[1]);
}

Vec3d Polygon::getVertex() const { return vertices[0]; }

int Polygon::getLayer() const { return layer; }