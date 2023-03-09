#include "color.hpp"
#include "vector_3d.hpp"

class Line {
  public:
    Line(Vec3d start_, Vec3d end_):start(start_), end(end_) {}
    Vec3d start;
    Vec3d end;
    Color color();
};