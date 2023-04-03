#include "tetris_piece.hpp"

class z_piece : public TetrisPiece3D5 {
 public:
  z_piece();

 public:
  bool canRotateXY() const override;
  bool canRotateXZ() const override;
  bool canRotateYZ() const override;
};