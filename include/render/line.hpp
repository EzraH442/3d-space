#pragma once
#include "vector_3d.hpp"
#include "color.hpp"

struct Line {
  int thickness;
  Vec3d start, end;
  Color color;
  Line(Vec3d start, Vec3d end, int thickness = 1);
  Line(Vec3d start, Vec3d end, Color &c, int thickness = 1);
};