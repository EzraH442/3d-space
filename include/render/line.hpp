#pragma once

#include <SDL.h>

#include "drawable_3d.hpp"

class Line : public Drawable3d {
  const int layer;

 public:
  const Vec3d start, end;

  Line();
  ~Line();
  Line(const Vec3d &start, const Vec3d &end, int layer = 0);
  Line(const Vec3d &start, const Vec3d &end, const Color &color, int layer = 0);

  Vec3d getMidpoint() const override;
  Vec3d getNormal() const override;
  Vec3d getVertex() const override;
  int getLayer() const override;
  void draw(const RenderFramework3d &fw, Context *context) const override;
};