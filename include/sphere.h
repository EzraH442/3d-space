#pragma once

#include "shape.h"

class Sphere : public Shape {

  private:
    int radius;

  public:
    ~Sphere();
    Sphere(int radius);
    Sphere(Vec3d pos, int radius);
    Sphere(Vec3d pos, int radius, Vec3d direction);
    void move(Vec3d pos) override;
    void rotate(Vec3d pos) override;
};