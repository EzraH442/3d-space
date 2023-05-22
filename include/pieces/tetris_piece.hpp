#pragma once

#include <vector>

#include "color.hpp"
#include "piece_multiarray.hpp"
#include "vector_3d.hpp"

class TetrisPiece3d {
 protected:
  PieceMultiarray dataArray;
  Color color;

 public:
  TetrisPiece3d();
  TetrisPiece3d(const Color& color, int length = 3);
  virtual ~TetrisPiece3d() = 0;

  void rotateXY(int r);
  void rotateXZ(int r);
  void rotateYZ(int r);

  void log();

  std::vector<Vec3d> getAbsolutePositions(const Vec3d& pos) const;
  std::vector<Vec3d> getRelativePositions() const;

  const Color getColor() const;
  const int getPieceLength() const;
  const PieceMultiarray getPieceMultiarray() const;
};