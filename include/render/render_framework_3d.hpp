#pragma once

#include <memory>
#include <vector>

#include "camera.hpp"
#include "game.hpp"
#include "render_framework.hpp"
#include "vector_2d.hpp"

class Drawable3d;

class RenderFramework3d : public RenderFramework {
 public:
  RenderFramework3d(int x, int y, int width, int height);

  Vec2d<float> getProjectedCoordinates(const Vec3d &v) const;

  void draw_text_3d(const Vec3d &pos, std::string s, SDL_Renderer *renderer);

  void draw_text_2d(const Vec2d<float> &pos, std::string s,
                    SDL_Renderer *renderer);

  void addBoard(const Board &b, SDL_Renderer *renderer);
  void addCube(const Cube &c);
  void addTetrisPiece(const TetrisPiece3d *piece, const Vec3d &pos);

 private:
  int x;
  int y;
  int height;
  int width;
  Camera c;

  virtual void renderObjects(SDL_Renderer *renderer) override;
  virtual void clearDrawables() override;
  virtual void drawDrawables(const std::function<void()> &f) override;

  std::vector<std::unique_ptr<Drawable3d>> toDraw;
};