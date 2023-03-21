#include "render/cube.hpp"

Cube::Cube() : strokeColor(Color::White), fillColor(Color::Purple) {
  points.fill({0, 0, 0});
}

Cube::Cube(const Cube &cube)
    : points(cube.points),
      strokeColor(cube.strokeColor),
      fillColor(cube.fillColor) {}

Cube::Cube(std::array<Vec3d, 8> points, const Color &sc, const Color &fc)
    : points(points), strokeColor(sc), fillColor(fc) {}

Cube::Cube(const Vec3d &pos, const Color &sc, const Color &fc)
    : strokeColor(sc), fillColor(fc) {
  const Vec3d p1 = pos;
  const Vec3d p2 = pos + Vec3d{1, 0, 0};
  const Vec3d p3 = pos + Vec3d{1, 1, 0};
  const Vec3d p4 = pos + Vec3d{0, 1, 0};

  const Vec3d p5 = pos + Vec3d{0, 0, 1};
  const Vec3d p6 = pos + Vec3d{1, 0, 1};
  const Vec3d p7 = pos + Vec3d{1, 1, 1};
  const Vec3d p8 = pos + Vec3d{0, 1, 1};

  points = {p1, p2, p3, p4, p5, p6, p7, p8};
}

const std::array<Line, 12> Cube::toLines() const {
  std::array<Line, 12> lines = {
      Line(points[0] * 10, points[1] * 10, strokeColor),
      Line(points[1] * 10, points[2] * 10, strokeColor),
      Line(points[2] * 10, points[3] * 10, strokeColor),
      Line(points[3] * 10, points[0] * 10, strokeColor),
      Line(points[4] * 10, points[5] * 10, strokeColor),
      Line(points[5] * 10, points[6] * 10, strokeColor),
      Line(points[6] * 10, points[7] * 10, strokeColor),
      Line(points[7] * 10, points[4] * 10, strokeColor),
      Line(points[0] * 10, points[4] * 10, strokeColor),
      Line(points[1] * 10, points[5] * 10, strokeColor),
      Line(points[2] * 10, points[6] * 10, strokeColor),
      Line(points[3] * 10, points[7] * 10, strokeColor),
  };
  return lines;
}

void Cube::log() {
  std::cout << "cube { ";
  for (auto &p : points) {
    std::cout << p << ", ";
  }
  std::cout << " }" << std::endl;
}