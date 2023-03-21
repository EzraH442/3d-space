#pragma once
#include "pieces/tetris_piece.hpp"

class TetrisPieceFactory {
 public:
  TetrisPieceFactory();
  AbstractTetrisPiece3d* createPiece(int id);
};