#pragma once

#include "pieces/tetris_piece.hpp"

class i_piece : public TetrisPiece3D5 {
 public:
  i_piece();

  bool canRotateXY(void) const override;
  bool canRotateXZ(void) const override;
  bool canRotateYZ(void) const override;
};