#include "render/drawable.hpp"

#include "SDL_render.h"
#include "color.hpp"
#include "render/framework.hpp"

Drawable::Drawable() {}
Drawable::~Drawable() {}
Drawable::Drawable(const Color& c) : color(c) {}

void Drawable::drawShape(const Framework* fw) const {
  SDL_SetRenderDrawColor(fw->renderer, color.r, color.g, color.b, color.a);
  draw(fw);
}