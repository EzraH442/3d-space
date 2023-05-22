#include "pieces/l_piece.hpp"

l_piece::l_piece() : TetrisPiece3d(Color::Orange) {
  dataArray.setFilled(0, 0, 1);
  dataArray.setFilled(0, 1, 1);
  dataArray.setFilled(0, 2, 1);
  dataArray.setFilled(1, 2, 1);
}
