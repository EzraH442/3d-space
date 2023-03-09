#pragma once

#include "structs.cpp"

int d = 1;

Vec2d lerp(Vec3d point) {
  double r = (double) d / point.z;
  return {((double) point.x) * r, ((double) point.y) * r};
}

