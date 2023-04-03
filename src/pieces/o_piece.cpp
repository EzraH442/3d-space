#include "pieces/o_piece.hpp"

o_piece::o_piece() : TetrisPiece3D5(Color::Yellow) {
  dataArray.setFilled(0, 0, 1);
  dataArray.setFilled(0, 1, 1);
  dataArray.setFilled(1, 1, 1);
  dataArray.setFilled(1, 0, 1);
}

bool o_piece::canRotateXY() const { return true; }
bool o_piece::canRotateXZ() const { return true; }
bool o_piece::canRotateYZ() const { return true; }