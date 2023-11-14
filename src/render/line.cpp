#include "render/line.hpp"

#include "render/render_framework_3d.hpp"
#include "vector_3d.hpp"

Line::Line() : Drawable3d(), layer(1), start(Vec3d()), end(Vec3d()) {}
Line::~Line() {}

Line::Line(const Vec3d &start, const Vec3d &end, int layer)
    : Drawable3d(Color::White), layer(layer), start(start), end(end) {}

Line::Line(const Vec3d &start, const Vec3d &end, const Color &c, int layer)
    : Drawable3d(c), layer(layer), start(start), end(end) {}

void Line::draw(const RenderFramework3d &fw, Context *context) const {
  Vec2d<float> start = fw.getProjectedCoordinates(this->start);
  Vec2d<float> end = fw.getProjectedCoordinates(this->end);

  // SDL_RenderDrawLine(context, start.x, start.y, end.x, end.y);
}

Vec3d Line::getMidpoint() const { return (end - start) / 2; }

Vec3d Line::getNormal() const { return {0, 0, 1}; }

Vec3d Line::getVertex() const { return start; }

int Line::getLayer() const { return layer; }