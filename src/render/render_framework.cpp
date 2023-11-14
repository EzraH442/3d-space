#include "render/render_framework.hpp"

#include <SDL.h>

#include <string>

#include "color.hpp"
#include "common.h"
#include "vector_2d.hpp"
void RenderFramework::render(Context* context, const std::function<void()>& f) {
  // SDL_SetRenderDrawColor(renderer, Color::Black.r, Color::Black.g,
  //                        Color::Black.b, Color::Black.a);

  // SDL_RenderClear(renderer);
  clearDrawables();
  drawDrawables(f);
  renderObjects(context);

  drawFPS(context);
  // SDL_RenderPresent(renderer);
}

void RenderFramework::drawFPS(Context* context) {
  std::string s("fps: " + std::to_string(fps));

  Vec2d<int> pos{10, 10};

  for (int i = 0; i < s.length(); i++) {
    // characterRGBA(renderer, pos.x + i * 8, pos.y, s[i], 255, 255, 255, 255);
  }
}

void RenderFramework::draw_text_2d(const Vec2d<float>& pos, std::string s,
                                   Context* context, const Color& c) const {
  for (size_t i = 0; i < s.length(); i++) {
    // characterRGBA(renderer, pos.x + i * 7, pos.y, s[i], c.r, c.g, c.b, c.a);
  }
}
