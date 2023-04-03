#include "pieces/s_piece.hpp"

s_piece::s_piece() : TetrisPiece3D5(Color::Green) {
  dataArray.setFilled(0, 1, 1);
  dataArray.setFilled(1, 0, 1);
  dataArray.setFilled(1, 1, 1);
  dataArray.setFilled(2, 0, 1);
}

bool s_piece::canRotateXY() const { return true; }
bool s_piece::canRotateXZ() const { return true; }
bool s_piece::canRotateYZ() const { return true; }