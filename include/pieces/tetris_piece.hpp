#pragma once

#include <vector>

#include "color.hpp"
#include "piece_multiarray.hpp"
#include "pieces/abstract_tetris_piece.hpp"
#include "vector_3d.hpp"

class TetrisPiece3D5 : public AbstractTetrisPiece3d {
 protected:
  PieceMultiarray dataArray;

 public:
  TetrisPiece3D5();
  TetrisPiece3D5(const Color& color, int length = 3);
  virtual ~TetrisPiece3D5() = 0;

  void rotateXY(int r) override;
  void rotateXZ(int r) override;
  void rotateYZ(int r) override;

  void log();

  std::vector<Vec3d> getAbsolutePositions(const Vec3d& pos) const override;
  std::vector<Vec3d> getRelativePositions() const override;
};