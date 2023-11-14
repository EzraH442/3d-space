#include "render/drawable_2d.hpp"

#include "render/render_framework_2d.hpp"

Drawable2d::Drawable2d() {}
Drawable2d::~Drawable2d() {}
Drawable2d::Drawable2d(const Color& c) : color(c) {}

void Drawable2d::drawShape(const RenderFramework2d& fw,
                           Context* context) const {
  // SDL_SetRenderDrawColor(context, color.r, color.g, color.b, color.a);
  draw(fw, context);
}