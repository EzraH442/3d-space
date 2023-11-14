#pragma once

#include <functional>
#include <string>

#include "render/drawable_2d.hpp"
#include "vector_2d.hpp"

class Button : public Drawable2d {
 public:
  Button(const Vec2d<size_t>& pos, const Vec2d<size_t>& dim, std::string text,
         const std::function<void(const SDL_MouseButtonEvent* e)>& onClick);
  ~Button() = default;

  void handleClick(const SDL_MouseButtonEvent* e) const;

 private:
  std::string text;
  Vec2d<size_t> pos;
  Vec2d<size_t> dim;
  std::function<void(const SDL_MouseButtonEvent* e)> onClick;

  void draw(const RenderFramework2d& fw, Context* context) const override;
};