#pragma once

#include <SDL.h>

#include <functional>

#include "color.hpp"
#include "render/context.hpp"
#include "vector_2d.hpp"

class RenderFramework {
 public:
  void render(Context* context, const std::function<void()>& f);
  virtual ~RenderFramework() = default;

  void drawFPS(Context* context);
  void draw_text_2d(const Vec2d<float>& pos, std::string s, Context* context,
                    const Color& = Color::White) const;

 protected:
  virtual void renderObjects(Context* context) = 0;
  virtual void clearDrawables() = 0;
  virtual void drawDrawables(const std::function<void()>& f) = 0;

 private:
};