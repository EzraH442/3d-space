#pragma once

#include <SDL.h>
#include <SDL2_gfxPrimitives.h>
#include <SDL_events.h>
#include <SDL_keycode.h>
#include <SDL_render.h>
#include <SDL_video.h>

#include <vector>

#include "board/board.hpp"
#include "render/camera.hpp"
#include "render/drawable.hpp"
#include "vector_2d.hpp"

class Drawable;
class Framework {
  int height;
  int width;

  Camera c;

  std::vector<Drawable const *> toDraw;

  void drawShapes();

 public:
  Framework(int height_, int width_);
  ~Framework();

  Vec2d<float> getProjectedCoordinates(const Vec3d &v) const;

  void addDrawable(Drawable const *d);

  void draw_text_3d(const Vec3d &pos, std::string s);

  void draw_text_2d(const Vec2d<float> &pos, std::string s);

  void addBoard(const Board &b);
  void addCube(const Cube &c);
  void addTetrisPiece(const TetrisPiece3d *piece, const Vec3d &pos);

  void moveCamera(const Vec3d &v);

  void display();
  void clear();
  SDL_Renderer *renderer = NULL;
  SDL_Window *window = NULL;
};