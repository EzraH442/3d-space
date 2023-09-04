#include "render/render_framework_2d.hpp"

#include <SDL2_gfxPrimitives.h>

#include <algorithm>

#include "SDL_render.h"
#include "render/drawable_2d.hpp"
#include "vector_2d.hpp"

RenderFramework2d::RenderFramework2d(int x, int y, int height, int width)
    : x(x), y(y), height(height), width(width) {}

void RenderFramework2d::renderObjects(SDL_Renderer *renderer) {
  for (const auto &d : toDraw) {
    d->drawShape(*this, renderer);
  }
}

void RenderFramework2d::clearDrawables() { toDraw.clear(); }

void RenderFramework2d::drawDrawables(const std::function<void()> &f) { f(); }

void RenderFramework2d::draw_text(const Vec2d<float> &pos, std::string s,
                                  SDL_Renderer *renderer) {
  for (int i = 0; i < s.length(); i++) {
    characterRGBA(renderer, pos.x, pos.y, s[i], 255, 255, 255, 255);
  }
}