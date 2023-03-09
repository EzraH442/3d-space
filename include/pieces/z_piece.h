#include "tetris_piece.h"

class z_piece : public AbstractTetrisPiece3D {
  public:
    z_piece();
  public:
    bool canRotateXY() override;
    bool canRotateXZ() override;
    bool canRotateYZ() override;
};