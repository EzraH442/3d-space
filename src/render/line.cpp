#include "render/line.hpp"

#include "render/render_framework_3d.hpp"

Line::Line() : Drawable3d(), thickness(1), start(Vec3d()), end(Vec3d()) {}
Line::~Line() {}

Line::Line(const Vec3d &start, const Vec3d &end, int t)
    : Drawable3d(Color::White), thickness(t), start(start), end(end) {}

Line::Line(const Vec3d &start, const Vec3d &end, const Color &c, int t)
    : Drawable3d(c), thickness(t), start(start), end(end) {}

void Line::draw(const RenderFramework3d &fw, SDL_Renderer *renderer) const {
  Vec2d<float> start = fw.getProjectedCoordinates(this->start);
  Vec2d<float> end = fw.getProjectedCoordinates(this->end);

  SDL_RenderDrawLine(renderer, start.x, start.y, end.x, end.y);
}

Vec3d Line::getMidpoint() const { return (end - start) / 2; }