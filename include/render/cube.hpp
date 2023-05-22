#pragma once

#include <vector>

#include "line.hpp"
#include "polygon.hpp"

class Cube {
  std::array<Vec3d, 8> points;
  const Color strokeColor;
  const Color fillColor;

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