#pragma once

#include "tetris_piece.hpp"

class l_piece : public TetrisPiece3D5 {
 public:
  l_piece();

 public:
  bool canRotateXY() override;
  bool canRotateXZ() override;
  bool canRotateYZ() override;
};