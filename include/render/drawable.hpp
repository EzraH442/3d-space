#pragma once

#include "SDL_render.h"
#include "color.hpp"
#include "vector_3d.hpp"

class Framework;
class Drawable {
 protected:
  const Color color;
  virtual void draw(const Framework* fw) const = 0;

 public:
  Drawable();
  Drawable(const Color& c);
  virtual ~Drawable() = 0;

  virtual Vec3d getMidpoint() const = 0;

  void drawShape(const Framework* fw) const;
};