#include "pieces/z_piece.hpp"

#include "pieces/tetris_piece.hpp"

z_piece::z_piece() : TetrisPiece3D5(Color::Red) {
  dataArray.setFilled(0, 0, 0);
  dataArray.setFilled(1, 0, 0);
  dataArray.setFilled(1, 1, 0);
  dataArray.setFilled(2, 1, 0);
}

bool z_piece::canRotateXY() { return true; }
bool z_piece::canRotateXZ() { return true; }
bool z_piece::canRotateYZ() { return true; }