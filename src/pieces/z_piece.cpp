#include "pieces/z_piece.hpp"

z_piece::z_piece() : TetrisPiece3d(Color::Red) {
  dataArray.setFilled(0, 0, 1);
  dataArray.setFilled(1, 0, 1);
  dataArray.setFilled(1, 1, 1);
  dataArray.setFilled(2, 1, 1);
}
