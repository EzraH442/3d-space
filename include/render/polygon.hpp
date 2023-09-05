#pragma once

#include <SDL.h>

#include <array>

#include "drawable_3d.hpp"

class Polygon : public Drawable3d {
  const std::array<Vec3d, 4> vertices;

 public:
  Polygon();
  ~Polygon();
  Polygon(const std::array<Vec3d, 4> vertices, const Color& c);

  Vec3d getMidpoint() const override;
  void draw(const RenderFramework3d& framework,
            SDL_Renderer* renderer) const override;
};