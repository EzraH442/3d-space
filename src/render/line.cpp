#include "render/line.hpp"

#include "render/drawable.hpp"
#include "render/framework.hpp"

Line::Line() : Drawable(), thickness(1), start(Vec3d()), end(Vec3d()) {}
Line::~Line() {}

Line::Line(const Vec3d &start, const Vec3d &end, int t)
    : Drawable(Color::White), thickness(t), start(start), end(end) {}

Line::Line(const Vec3d &start, const Vec3d &end, const Color &c, int t)
    : Drawable(c), thickness(t), start(start), end(end) {}

void Line::draw(const Framework *fw) const {
  Vec2d<float> start = fw->getProjectedCoordinates(this->start);
  Vec2d<float> end = fw->getProjectedCoordinates(this->end);

  SDL_RenderDrawLine(fw->renderer, start.x, start.y, end.x, end.y);
}

Vec3d Line::getMidpoint() const { return (end - start) / 2; }