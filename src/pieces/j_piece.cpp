#include "pieces/j_piece.hpp"

j_piece::j_piece() : TetrisPiece3d(Color::Blue) {
  dataArray.setFilled(0, 2, 1);
  dataArray.setFilled(1, 0, 1);
  dataArray.setFilled(1, 1, 1);
  dataArray.setFilled(1, 2, 1);
}
