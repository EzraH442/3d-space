#include "render/drawable_3d.hpp"

#include "render/render_framework_3d.hpp"

Drawable3d::Drawable3d() {}
Drawable3d::~Drawable3d() {}
Drawable3d::Drawable3d(const Color& c) : color(c) {}

void Drawable3d::drawShape(const RenderFramework3d& fw,
                           Context* context) const {
  // SDL_SetRenderDrawColor(context, color.r, color.g, color.b, color.a);
  draw(fw, context);
}