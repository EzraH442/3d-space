#include "color.hpp"
#include "vector_3d.hpp"

struct Cube {
  Color color;
  Vec3d pos;
  Cube(): color(Color()), pos({0,0,0}) {}
  Cube(Color c, Vec3d p): color(c), pos(p) {}
};