#pragma once
#include "pieces/tetris_piece.hpp"

class TetrisPieceFactory {
 public:
  TetrisPieceFactory();
  TetrisPiece3d* createPiece(int id);
};