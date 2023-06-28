#pragma once

#include <vector_3d.hpp>

class Camera {
  Vec3d pos;
  int defaultHeight;
  int length;  // total length of "board / playing area"

 public:
  Camera(int boardLength);

  void move(const Vec3d& v);
  Vec3d getPos() const;
};