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
  bool isBackface(const Drawable3d &d) const;

  void draw_text_3d(const Vec3d &pos, std::string s, Context *context);

  void addBoard(const Board &b, Context *context);
  void addCube(const Cube &c);
  void addTetrisPiece(const TetrisPiece3d *piece, const Vec3d &pos);
  Camera c;

 private:
  int x;
  int y;
  int height;
  int width;

  virtual void renderObjects(Context *context) override;
  virtual void clearDrawables() override;
  virtual void drawDrawables(const std::function<void()> &f) override;

  std::array<std::vector<std::unique_ptr<Drawable3d>>, 20> toDraw;
  std::vector<std::unique_ptr<Drawable3d>> baseLayer;
};