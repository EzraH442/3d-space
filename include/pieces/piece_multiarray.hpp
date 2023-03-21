#pragma once

#include <array>
#include <vector>

#include "vector_3d.hpp"

class PieceMultiarray {
  std::array<bool, 27> data;

 public:
  PieceMultiarray();

  void log();
  void logRaw();

  bool isFilled(int x, int y, int z) const;
  bool isFilled(int n) const;
  bool setFilled(int x, int y, int z, int filled = 1);
  bool setFilled(int n, int filled = 1);

  void rotateXY(int r);
  void rotateXZ(int r);
  void rotateYZ(int r);

  std::vector<Vec3d> getAbsolutePositions(const Vec3d& pos) const;
  std::vector<Vec3d> getRelativePositions() const;
};
