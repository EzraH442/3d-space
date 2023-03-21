#pragma once

#include <optional>
#include <set>

#include "board/bag.hpp"
#include "board/board.hpp"
#include "pieces/abstract_tetris_piece.hpp"
#include "pieces/piece_factory.hpp"
#include "pieces/tetris_piece.hpp"
#include "vector_3d.hpp"

class Game {
  Bag bag;
  int currentPieceId;
  int currentHeldId;
  bool canHold;
  Vec3d currentPiecePos;
  TetrisPieceFactory tpf;

 public:
  Game();
  AbstractTetrisPiece3d* currentPiece;
  Vec3d getCurrentPiecePos() const;

  void hardDrop(Board& board);
  int tryHold();
};