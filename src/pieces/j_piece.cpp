#include "pieces/j_piece.hpp"

#include "pieces/tetris_piece.hpp"

j_piece::j_piece() : TetrisPiece3D5(Color::Blue) {
  dataArray.setFilled(0, 2, 0);
  dataArray.setFilled(1, 0, 0);
  dataArray.setFilled(1, 1, 0);
  dataArray.setFilled(1, 2, 0);
}

bool j_piece::canRotateXY() { return true; }
bool j_piece::canRotateXZ() { return true; }
bool j_piece::canRotateYZ() { return true; }