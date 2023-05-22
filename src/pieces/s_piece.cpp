#include "pieces/s_piece.hpp"

s_piece::s_piece() : TetrisPiece3d(Color::Green) {
  dataArray.setFilled(0, 1, 1);
  dataArray.setFilled(1, 0, 1);
  dataArray.setFilled(1, 1, 1);
  dataArray.setFilled(2, 0, 1);
}
