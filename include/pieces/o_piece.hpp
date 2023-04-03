#pragma once

#include "tetris_piece.hpp"

class o_piece : public TetrisPiece3d {
 public:
  o_piece();

  bool canRotateXY() const override;
  bool canRotateXZ() const override;
  bool canRotateYZ() const override;
  void log();
};