#pragma once

#include "tetris_piece.hpp"

class s_piece : public TetrisPiece3D5 {
 public:
  s_piece();

 public:
  bool canRotateXY() override;
  bool canRotateXZ() override;
  bool canRotateYZ() override;
};