#include "pieces/i_piece.hpp"

i_piece::i_piece() : TetrisPiece3d(Color::Cyan, 4) {
  dataArray.setFilled(0, 1, 1);
  dataArray.setFilled(1, 1, 1);
  dataArray.setFilled(2, 1, 1);
  dataArray.setFilled(3, 1, 1);
}
