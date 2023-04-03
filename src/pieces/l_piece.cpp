#include "pieces/l_piece.hpp"

l_piece::l_piece() : TetrisPiece3D5(Color::Orange) {
  dataArray.setFilled(0, 0, 1);
  dataArray.setFilled(0, 1, 1);
  dataArray.setFilled(0, 2, 1);
  dataArray.setFilled(1, 2, 1);
}

bool l_piece::canRotateXY() const { return true; }
bool l_piece::canRotateXZ() const { return true; }
bool l_piece::canRotateYZ() const { return true; }