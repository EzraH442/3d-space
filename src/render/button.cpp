#include "render/button.hpp"

#include <SDL2_gfxPrimitives.h>

#include "render/drawable_2d.hpp"
#include "render/render_framework_2d.hpp"
#include "vector_2d.hpp"

Button::Button(
    const Vec2d<size_t>& pos, const Vec2d<size_t>& dim, std::string text,
    const std::function<void(const SDL_MouseButtonEvent* e)>& onClick)
    : Drawable2d(Color::Cyan),
      text(text),
      pos(pos),
      dim(dim),
      onClick(onClick) {}

void Button::draw(const RenderFramework2d& fw, SDL_Renderer* renderer) const {
  std::array<Vec2d<size_t>, 4> vertices;
  vertices[0] = pos;
  vertices[1] = Vec2d<size_t>{pos.x + dim.x, pos.y};
  vertices[2] = Vec2d<size_t>{pos.x + dim.x, pos.y + dim.y};
  vertices[3] = Vec2d<size_t>{pos.x, pos.y + dim.y};

  short vx[5];
  short vy[5];

  for (int i = 0; i < 5; i++) {
    vx[i] = (short)vertices[i % 4].x;
    vy[i] = (short)vertices[i % 4].y;
  }

  filledPolygonRGBA(renderer, vx, vy, vertices.size(), color.r, color.g,
                    color.b, color.a);

  fw.draw_text(Vec2d<float>{static_cast<float>(pos.x + dim.x / 2 -
                                               text.length() * 6 / 2),
                            static_cast<float>(pos.y + dim.y / 2 - 4)},
               text, renderer);
}

void Button::handleClick(const SDL_MouseButtonEvent* e) const {
  int x = e->x;
  int y = e->y;

  if (x >= pos.x && x < pos.x + dim.x && y >= pos.y && y <= pos.y + dim.y) {
    onClick(e);
  }
}