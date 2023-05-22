#pragma once

#include "SDL_render.h"
#include "color.hpp"
#include "drawable.hpp"

class Line : public Drawable {
  int thickness;

 public:
  const Vec3d start, end;

  Line();
  ~Line();
  Line(const Vec3d &start, const Vec3d &end, int thickness = 1);
  Line(const Vec3d &start, const Vec3d &end, const Color &color,
       int thickness = 1);

  Vec3d getMidpoint() const override;
  void draw(const Framework *fw) const override;
};