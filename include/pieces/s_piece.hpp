#pragma once

#include "tetris_piece.hpp"

class s_piece : public TetrisPiece3d {
 public:
  s_piece();

 public:
  bool canRotateXY() const override;
  bool canRotateXZ() const override;
  bool canRotateYZ() const override;
};