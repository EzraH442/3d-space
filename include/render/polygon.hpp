#pragma once

#include <array>

#include "drawable.hpp"

class Polygon : public Drawable {
  const std::array<Vec3d, 4> vertices;

 public:
  Polygon();
  ~Polygon();
  Polygon(const std::array<Vec3d, 4> vertices, const Color& c);

  Vec3d getMidpoint() const override;
  void draw(const Framework* renderer) const override;
};