#include "render/cube.hpp"

#include <algorithm>
#include <array>

#include "render/polygon.hpp"
#include "vector_3d.hpp"

Vec3d Cube::calcCenter(const std::array<Vec3d, 8> &pts) {
  Vec3d sum{0, 0, 0};

  for (const auto p : pts) {
    sum = sum + p;
  }

  sum = sum / 8;

  return sum;
}

std::array<Vec3d, 8> Cube::makePointArray(const Vec3d &pos) {
  const Vec3d p1 = pos * 10;
  const Vec3d p2 = pos * 10 + Vec3d{10, 0, 0};
  const Vec3d p3 = pos * 10 + Vec3d{10, 10, 0};
  const Vec3d p4 = pos * 10 + Vec3d{0, 10, 0};

  const Vec3d p5 = pos * 10 + Vec3d{0, 0, 10};
  const Vec3d p6 = pos * 10 + Vec3d{10, 0, 10};
  const Vec3d p7 = pos * 10 + Vec3d{10, 10, 10};
  const Vec3d p8 = pos * 10 + Vec3d{0, 10, 10};

  return {p1, p2, p3, p4, p5, p6, p7, p8};
}

Cube::Cube()
    : strokeColor(Color::White),
      fillColor(Color::Purple),
      center(Vec3d{0, 0, 0}) {
  points.fill({0, 0, 0});
}

Cube::Cube(const Cube &cube)
    : points(cube.points),
      strokeColor(cube.strokeColor),
      fillColor(cube.fillColor),
      center(calcCenter(points)) {}

Cube::Cube(std::array<Vec3d, 8> points, const Color &sc, const Color &fc)
    : points(points),
      strokeColor(sc),
      fillColor(fc),
      center(calcCenter(points)) {}

Cube::Cube(const Vec3d &pos, const Color &sc, const Color &fc)
    : points(makePointArray(pos)),
      strokeColor(sc),
      fillColor(fc),
      center(calcCenter(points)) {}

Vec3d minOffset(const Vec3d &center, const Vec3d &point, int plane) {
  int minDistance = 2147483647;
  Vec3d minOffset;

  int Z_PLANE = 0;
  int Y_PLANE = 1;
  int X_PLANE = 2;

  for (int i = 0; i < 4; i++) {
    Vec3d offset;
    if (plane == Z_PLANE) {
      offset = {offsets[i].first, offsets[i].second, 0};
    }
    if (plane == Y_PLANE) {
      offset = {offsets[i].first, 0, offsets[i].second};
    }
    if (plane == X_PLANE) {
      offset = {0, offsets[i].first, offsets[i].second};
    }
    int distance = (center - (point + offset)).squaredMagnitude();
    if (distance < minDistance) {
      minDistance = distance;
      minOffset = offset;
    }
  }

  return minOffset;
}

const Color Silver(192, 192, 192);

const std::vector<Polygon> Cube::toLines() const {
  std::vector<Polygon> ret;

  // 3 types:
  // - i+4   (i+1) % 4 + 4
  // - i     i+4
  // - i     (i+1) % 4

  for (int i = 0; i < 4; i++) {
    Vec3d p1 = points[i + 4];
    Vec3d p2 = points[(i + 1) % 4 + 4];
    ret.push_back(Polygon(
        {
            p1,
            p2,
            p2 + minOffset(center, p2, 0),
            p1 + minOffset(center, p1, 0),
        },
        Silver));
  }

  for (int i = 0; i < 4; i++) {
    Vec3d p1 = points[i];
    Vec3d p2 = points[i + 4];
    ret.push_back(Polygon(
        {
            p1,
            p2,
            p2 + minOffset(center, p2, 1),
            p1 + minOffset(center, p1, 1),
        },
        Silver));
  }

  for (int i = 0; i < 4; i++) {
    Vec3d p1 = points[i];
    Vec3d p2 = points[(i + 1) % 4];
    ret.push_back(Polygon(
        {
            p1,
            p2,
            p2 + minOffset(center, p2, 1),
            p1 + minOffset(center, p1, 1),
        },
        Silver));
  }

  return ret;
}

void Cube::log() {
  std::cout << "cube { ";
  for (auto &p : points) {
    std::cout << p << ", ";
  }
  std::cout << " }" << std::endl;
}

const std::vector<Polygon> Cube::toPolygons() const {
  std::vector<Polygon> ret;

  // top face
  ret.push_back(
      Polygon({points[4], points[5], points[6], points[7]}, fillColor));

  // side faces (bottom face should never be visible)
  for (int i = 0; i < 4; i++) {
    ret.push_back(Polygon(
        {
            points[i],
            points[i + 4],
            points[(i + 1) % 4 + 4],
            points[(i + 1) % 4],
        },
        fillColor));
  }

  return ret;
}

const Color Cube::getFillColor() const { return fillColor; }