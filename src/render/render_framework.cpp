#include "render/render_framework.hpp"

#include <SDL2_gfxPrimitives.h>
#include <SDL_render.h>

#include <string>

#include "color.hpp"
#include "common.h"
#include "vector_2d.hpp"

void RenderFramework::render(SDL_Renderer* renderer,
                             const std::function<void()>& f) {
  SDL_SetRenderDrawColor(renderer, Color::Black.r, Color::Black.g,
                         Color::Black.b, Color::Black.a);

  SDL_RenderClear(renderer);
  clearDrawables();
  drawDrawables(f);
  renderObjects(renderer);

  drawFPS(renderer);
  SDL_RenderPresent(renderer);
}

void RenderFramework::drawFPS(SDL_Renderer* renderer) {
  std::string s("fps: " + std::to_string(fps));

  Vec2d<int> pos{10, 10};

  for (int i = 0; i < s.length(); i++) {
    characterRGBA(renderer, pos.x + i * 8, pos.y, s[i], 255, 255, 255, 255);
  }
}