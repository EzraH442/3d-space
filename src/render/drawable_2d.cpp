#include "render/drawable_2d.hpp"

#include "SDL_render.h"
#include "render/render_framework_2d.hpp"

Drawable2d::Drawable2d() {}
Drawable2d::~Drawable2d() {}
Drawable2d::Drawable2d(const Color& c) : color(c) {}

void Drawable2d::drawShape(const RenderFramework2d& fw,
                           SDL_Renderer* renderer) const {
  SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
  draw(fw, renderer);
}