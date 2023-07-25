#include "render/render_framework.hpp"

#include "color.hpp"

void RenderFramework::render(SDL_Renderer *renderer) {
  SDL_SetRenderDrawColor(renderer, Color::Black.r, Color::Black.g,
                         Color::Black.b, Color::Black.a);

  SDL_RenderClear(renderer);
  clearDrawables();
  drawDrawables();

  renderObjects(renderer);
  SDL_RenderPresent(renderer);
}
