#include "pieces/t_piece.hpp"

t_piece::t_piece() : TetrisPiece3d(Color::Purple) {
  dataArray.setFilled(0, 1, 1);
  dataArray.setFilled(1, 0, 1);
  dataArray.setFilled(1, 1, 1);
  dataArray.setFilled(2, 1, 1);
}
