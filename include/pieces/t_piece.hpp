#pragma once

#include "tetris_piece.hpp"

class t_piece : public TetrisPiece3D5 {
 public:
  t_piece();

 public:
  bool canRotateXY() const override;
  bool canRotateXZ() const override;
  bool canRotateYZ() const override;
};