#pragma once

#include "tetris_piece.hpp"

class j_piece : public TetrisPiece3d {
 public:
  j_piece();

 public:
  bool canRotateXY() const override;
  bool canRotateXZ() const override;
  bool canRotateYZ() const override;
};