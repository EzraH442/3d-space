#pragma once

#include <SDL.h>

#include "color.hpp"
#include "vector_3d.hpp"

class RenderFramework3d;

class Drawable3d {
 protected:
  const Color color;
  virtual void draw(const RenderFramework3d& fw,
                    SDL_Renderer* renderer) const = 0;

 public:
  Drawable3d();
  Drawable3d(const Color& c);
  virtual ~Drawable3d() = 0;

  virtual Vec3d getMidpoint() const = 0;

  void drawShape(const RenderFramework3d& fw, SDL_Renderer* renderer) const;
};