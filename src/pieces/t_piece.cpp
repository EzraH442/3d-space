#include "pieces/t_piece.hpp"

#include "pieces/tetris_piece.hpp"

t_piece::t_piece() : TetrisPiece3D5(Color::Purple) {
  dataArray.setFilled(0, 1, 0);
  dataArray.setFilled(1, 0, 0);
  dataArray.setFilled(1, 1, 0);
  dataArray.setFilled(2, 1, 0);
}

bool t_piece::canRotateXY() { return true; }
bool t_piece::canRotateXZ() { return true; }
bool t_piece::canRotateYZ() { return true; }