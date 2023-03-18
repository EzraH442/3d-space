#include "render/line.hpp"

Line::Line(Vec3d start, Vec3d end, int t): 
  thickness(t), start(start), end(end) 
{
  color = Color();
}

Line::Line(Vec3d start, Vec3d end, Color &c, int t): 
  thickness(t), start(start), end(end), color(c) {}