#pragma once

#include <memory>
#include <string>
#include <vector>

#include "drawable_2d.hpp"
#include "render_framework.hpp"
#include "vector_2d.hpp"

// class Drawable2d;

class RenderFramework2d : public RenderFramework {
 public:
  RenderFramework2d(int x, int y, int width, int height);

  void draw_text(const Vec2d<float> &pos, std::string s,
                 SDL_Renderer *renderer);

 private:
  int x;
  int y;
  int height;
  int width;

  virtual void renderObjects(SDL_Renderer *renderer) override;
  virtual void clearDrawables() override;
  virtual void drawDrawables(const std::function<void()> &f) override;

  std::vector<std::unique_ptr<Drawable2d>> toDraw;
};