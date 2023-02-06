#pragma once

#include "shape.h"

class Cylinder: public Shape {

  private:
    int radius;
    int height;
  
  public:
    ~Cylinder();
    Cylinder(int radius, int height);
    Cylinder(Vec3d pos, int radius, int height);
    Cylinder(Vec3d pos, int radius, int height, Vec3d direction);
    void move(Vec3d pos) override;
    void rotate(Vec3d pos) override;
};