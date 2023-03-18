#pragma once
#include <array>
#include "vector_3d.hpp"
#include "color.hpp"
#include "line.hpp"

class Cube {
  std::array<Vec3d, 8> points;
  Color strokeColor;
  Color fillColor;

  public:
    Cube();
    Cube(std::array<Vec3d, 8> points, Color strokeColor, Color fillColor);
    Cube(Vec3d pos, Color strokeColor, Color fillColor);
    std::array<Line, 12> toLines();
    void log();
};