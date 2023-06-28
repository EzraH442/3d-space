#pragma once

#include <memory>

#include "enums.hpp"
#include "pieces/tetris_piece.hpp"

class TetrisPieceFactory {
 public:
  TetrisPieceFactory();
  std::unique_ptr<TetrisPiece3d> createPiece(const PieceType& type);
};