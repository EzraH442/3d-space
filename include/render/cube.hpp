#pragma once

#include <array>

#include "color.hpp"
#include "line.hpp"
#include "vector_3d.hpp"

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
  const std::array<Line, 12> toLines() const;
  void log();
};