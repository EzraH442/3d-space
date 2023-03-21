#pragma once

#include <vector>

#include "vector_3d.hpp"

class AbstractTetrisPiece3d {
 public:
  AbstractTetrisPiece3d();
  virtual ~AbstractTetrisPiece3d() = 0;

  virtual bool canRotateXY(void) = 0;
  virtual bool canRotateXZ(void) = 0;
  virtual bool canRotateYZ(void) = 0;

  virtual void rotateXY(int r) = 0;
  virtual void rotateXZ(int r) = 0;
  virtual void rotateYZ(int r) = 0;

  virtual std::vector<Vec3d> getAbsolutePositions(const Vec3d& pos) const = 0;
  virtual std::vector<Vec3d> getRelativePositions() const = 0;
};