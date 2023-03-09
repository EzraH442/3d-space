#pragma once
#include "tetris_piece.h"

class s_piece : public AbstractTetrisPiece3D {
  public:
    s_piece();
  public:
    bool canRotateXY() override;
    bool canRotateXZ() override;
    bool canRotateYZ() override;
};