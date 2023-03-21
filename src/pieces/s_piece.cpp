#include "pieces/s_piece.hpp"

#include "pieces/tetris_piece.hpp"

s_piece::s_piece() : TetrisPiece3D5(Color::Green) {
  dataArray.setFilled(0, 1, 0);
  dataArray.setFilled(1, 0, 0);
  dataArray.setFilled(1, 1, 0);
  dataArray.setFilled(2, 0, 0);
}

bool s_piece::canRotateXY() { return true; }
bool s_piece::canRotateXZ() { return true; }
bool s_piece::canRotateYZ() { return true; }