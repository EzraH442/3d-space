#pragma once

#include "tetris_piece.hpp"

class j_piece : public TetrisPiece3D5 {
 public:
  j_piece();

 public:
  bool canRotateXY() const override;
  bool canRotateXZ() const override;
  bool canRotateYZ() const override;
};