#pragma once

#include <SDL.h>

#include <array>

#include "drawable_3d.hpp"

class Polygon : public Drawable3d {
  const std::array<Vec3d, 4> vertices;
  const int layer;

 public:
  Polygon();
  ~Polygon();
  Polygon(const std::array<Vec3d, 4> vertices, const Color& c, int layer);

  Vec3d getMidpoint() const override;
  Vec3d getNormal() const override;
  Vec3d getVertex() const override;
  int getLayer() const override;

  void draw(const RenderFramework3d& framework,
            SDL_Renderer* renderer) const override;
};