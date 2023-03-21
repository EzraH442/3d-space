#include "tetris_piece.hpp"

class z_piece : public TetrisPiece3D5 {
 public:
  z_piece();

 public:
  bool canRotateXY() override;
  bool canRotateXZ() override;
  bool canRotateYZ() override;
};