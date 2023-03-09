#include "pieces/l_piece.hpp"

l_piece::l_piece() {
  dataArray.setFilled(0, 0, 0);
  dataArray.setFilled(0, 1, 0);
  dataArray.setFilled(0, 2, 0);
  dataArray.setFilled(1, 2, 0);
}

bool l_piece::canRotateXY() { return true; }
bool l_piece::canRotateXZ() { return true; }
bool l_piece::canRotateYZ() { return true; }