#pragma once

#include <SDL.h>

#include "drawable_3d.hpp"

class Line : public Drawable3d {
  int thickness;

 public:
  const Vec3d start, end;

  Line();
  ~Line();
  Line(const Vec3d &start, const Vec3d &end, int thickness = 1);
  Line(const Vec3d &start, const Vec3d &end, const Color &color,
       int thickness = 1);

  Vec3d getMidpoint() const override;
  Vec3d getNormal() const override;
  Vec3d getVertex() const override;
  void draw(const RenderFramework3d &fw, SDL_Renderer *renderer) const override;
};