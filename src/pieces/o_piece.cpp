#include "pieces/o_piece.hpp"

o_piece::o_piece() : TetrisPiece3d(Color::Yellow) {
  dataArray.setFilled(0, 0, 1);
  dataArray.setFilled(0, 1, 1);
  dataArray.setFilled(1, 1, 1);
  dataArray.setFilled(1, 0, 1);
}
