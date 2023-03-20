#pragma once

#include <array>

#include "color.hpp"
#include "line.hpp"
#include "vector_3d.hpp"

class Cube {
  std::array<Vec3d, 8> points;
  Color strokeColor;
  Color fillColor;

 public:
  Cube();
  Cube(std::array<Vec3d, 8> points, Color &strokeColor, Color &fillColor);
  Cube(Vec3d pos, Color &strokeColor, Color &fillColor);
  const std::array<Line, 12> toLines() const;
  void log();
};