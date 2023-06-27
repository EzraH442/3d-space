#pragma once

#include <vector>

#include "line.hpp"
#include "polygon.hpp"

const std::array<std::pair<int, int>, 4> offsets = {
    {{-1, -1}, {-1, 1}, {1, -1}, {1, 1}}};

class Cube {
  std::array<Vec3d, 8> points;
  const Color strokeColor;
  const Color fillColor;
  const Vec3d center;

  static Vec3d calcCenter(const std::array<Vec3d, 8> &);
  static std::array<Vec3d, 8> makePointArray(const Vec3d &center);

 public:
  Cube();
  Cube(const Cube &);
  Cube(std::array<Vec3d, 8> points, const Color &strokeColor,
       const Color &fillColor);
  Cube(const Vec3d &pos, const Color &strokeColor, const Color &fillColor);
  const std::vector<Drawable const *> toLines() const;
  const std::vector<Drawable const *> toPolygons() const;
  const Color getFillColor() const;
  void log();
};