#pragma once

#include "structs.cpp"
#include "color.h"

class WorldObject {

  protected:
    Color color;
  public:

  virtual ~WorldObject() = 0;
  virtual void move(Vec3d newPos) = 0;
  virtual void rotate(Vec3d newDir) = 0;

  Color getColor();
  void setColor(Color color);
};