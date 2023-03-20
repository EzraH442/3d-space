#pragma once

#include "tetris_piece.hpp"

class j_piece : public AbstractTetrisPiece3D {
 public:
  j_piece();

 public:
  bool canRotateXY() override;
  bool canRotateXZ() override;
  bool canRotateYZ() override;
};