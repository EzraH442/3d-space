#pragma once

#include "piece_multiarray.hpp"

class AbstractTetrisPiece3D {
 protected:
  PieceMultiarray dataArray = PieceMultiarray();

 public:
  AbstractTetrisPiece3D() {}
  virtual ~AbstractTetrisPiece3D() = 0;

  virtual bool canRotateXY(void) = 0;
  virtual bool canRotateXZ(void) = 0;
  virtual bool canRotateYZ(void) = 0;

  void rotateXY(int r);
  void rotateXZ(int r);
  void rotateYZ(int r);

  void log();
};