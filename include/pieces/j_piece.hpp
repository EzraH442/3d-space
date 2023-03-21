#pragma once

#include "tetris_piece.hpp"

class j_piece : public TetrisPiece3D5 {
 public:
  j_piece();

 public:
  bool canRotateXY() override;
  bool canRotateXZ() override;
  bool canRotateYZ() override;
};