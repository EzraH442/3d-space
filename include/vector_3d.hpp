#pragma once

#include <cmath>
#include <iostream>

struct Vec3d {
  int x, y, z;

  int squaredMagnitude() const;
};

Vec3d operator+(const Vec3d &, const Vec3d &);
Vec3d operator-(const Vec3d &, const Vec3d &);
Vec3d operator*(const Vec3d &, int);
int operator*(const Vec3d &, const Vec3d &);
Vec3d operator/(const Vec3d &, int);

Vec3d operator^(const Vec3d &, const Vec3d &);

std::ostream &operator<<(std::ostream &os, const Vec3d &);