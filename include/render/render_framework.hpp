#pragma once

#include <SDL_render.h>

#include <functional>

class RenderFramework {
 public:
  void render(SDL_Renderer* renderer, const std::function<void()>& f);
  virtual ~RenderFramework() = default;

  void drawFPS(SDL_Renderer* renderer);

 protected:
  virtual void renderObjects(SDL_Renderer* renderer) = 0;
  virtual void clearDrawables() = 0;
  virtual void drawDrawables(const std::function<void()>& f) = 0;

 private:
};