#pragma once
#include "tetris_piece.h"

class t_piece : public AbstractTetrisPiece3D {
  public:
    t_piece();
  public:
    bool canRotateXY() override;
    bool canRotateXZ() override;
    bool canRotateYZ() override;
};