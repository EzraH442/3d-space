#pragma once

#include "./worldobject.h"

class Shape : public WorldObject {

  protected:
    Vec3d position;

  public:
    virtual ~Shape() {};
};