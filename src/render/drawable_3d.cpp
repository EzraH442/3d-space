#include "render/drawable_3d.hpp"

#include "render/render_framework_3d.hpp"

Drawable3d::Drawable3d() {}
Drawable3d::~Drawable3d() {}
Drawable3d::Drawable3d(const Color& c) : color(c) {}

void Drawable3d::drawShape(const RenderFramework3d& fw,
                           SDL_Renderer* renderer) const {
  SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
  draw(fw, renderer);
}