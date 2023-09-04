#pragma once

#include <ostream>
template <typename T>

struct Vec2d {
  T x, y;
};

template <typename T>
std::ostream &operator<<(std::ostream &os, const Vec2d<T> &v) {
  os << "{"
     << " " << v.x << ", " << v.y << ", "
     << " }";
  return os;
};