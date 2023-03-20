#include "render/line.hpp"

Line::Line(const Vec3d &start, const Vec3d &end, int t)
    : thickness(t), start(start), end(end) {
  color = Color::White;
}

Line::Line(const Vec3d &start, const Vec3d &end, const Color &c, int t)
    : thickness(t), start(start), end(end), color(c) {}