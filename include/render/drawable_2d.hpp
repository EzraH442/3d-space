#pragma once

#include "SDL.h"
#include "color.hpp"

class RenderFramework2d;

class Drawable2d {
 protected:
  const Color color;
  virtual void draw(const RenderFramework2d& fw,
                    SDL_Renderer* renderer) const = 0;

 public:
  Drawable2d();
  Drawable2d(const Color& c);
  virtual ~Drawable2d() = 0;

  void drawShape(const RenderFramework2d& fw, SDL_Renderer* renderer) const;
};