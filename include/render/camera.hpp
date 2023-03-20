#pragma once

#include <vector_3d.hpp>

class Camera {
  int height = 300;
  int length = 100;  // total length of "board / playing area"
  int offset = 25;

 public:
  Camera();

  void changeHeight(int n);
  void changeOffset(int n);
  int getHeight() const;
  int getOffset() const;

  Vec3d getPos(int dir) const;
};