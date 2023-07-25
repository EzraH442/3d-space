#pragma once

#include "SDL_render.h"

class RenderFramework {
 public:
  void render(SDL_Renderer* renderer);
  virtual ~RenderFramework() = default;

 protected:
  virtual void renderObjects(SDL_Renderer* renderer) = 0;
  virtual void clearDrawables() = 0;
  virtual void drawDrawables() = 0;

 private:
};