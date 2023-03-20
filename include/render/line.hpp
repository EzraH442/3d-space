#pragma once

#include "color.hpp"
#include "vector_3d.hpp"

struct Line {
  int thickness;
  Vec3d start, end;
  Color color;
  Line(const Vec3d &start, const Vec3d &end, int thickness = 1);
  Line(const Vec3d &start, const Vec3d &end, const Color &color,
       int thickness = 1);
};