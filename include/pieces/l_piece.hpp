#pragma once

#include "tetris_piece.hpp"

class l_piece : public TetrisPiece3d {
 public:
  l_piece();

 public:
  bool canRotateXY() const override;
  bool canRotateXZ() const override;
  bool canRotateYZ() const override;
};