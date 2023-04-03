#pragma once

#include "tetris_piece.hpp"

class s_piece : public TetrisPiece3D5 {
 public:
  s_piece();

 public:
  bool canRotateXY() const override;
  bool canRotateXZ() const override;
  bool canRotateYZ() const override;
};