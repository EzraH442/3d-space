#pragma once

#include <SDL.h>

#include <functional>

#include "color.hpp"
#include "vector_2d.hpp"

class RenderFramework {
 public:
  void render(SDL_Renderer* renderer, const std::function<void()>& f);
  virtual ~RenderFramework() = default;

  void drawFPS(SDL_Renderer* renderer);
  void draw_text_2d(const Vec2d<float>& pos, std::string s,
                    SDL_Renderer* renderer, const Color& = Color::White) const;

 protected:
  virtual void renderObjects(SDL_Renderer* renderer) = 0;
  virtual void clearDrawables() = 0;
  virtual void drawDrawables(const std::function<void()>& f) = 0;

 private:
};