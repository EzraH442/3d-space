#pragma once

#include <vector>

#include "vector_3d.hpp"

class PieceMultiarray {
  const int length;
  std::vector<bool> data;

 public:
  PieceMultiarray();
  PieceMultiarray(int length);

  void log();
  void logRaw();

  bool isFilled(int x, int y, int z) const;
  bool isFilled(int n) const;
  bool setFilled(int x, int y, int z, int filled = 1);
  bool setFilled(int n, int filled = 1);

  void rotateXY(int r);
  void rotateXZ(int r);
  void rotateYZ(int r);

  void rotate(const Vec3d& rotation);

  const int getLength() const;

  std::vector<Vec3d> getAbsolutePositions(const Vec3d& pos) const;
};
