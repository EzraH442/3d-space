#pragma once

#include "./worldobject.h"

class Shape : public WorldObject {

  protected:
    Vec3d position;
    Vec3d direction;

  public:
    virtual ~Shape() {};
};