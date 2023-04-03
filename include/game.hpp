#pragma once

#include "board/bag.hpp"
#include "board/board.hpp"
#include "pieces/piece_factory.hpp"
#include "pieces/tetris_piece.hpp"

class Game {
  TetrisPiece3d* currentPiece;
  Bag bag;
  int currentPieceId;
  int currentHeldId;
  bool canHold;
  Vec3d currentPiecePos;
  TetrisPieceFactory tpf;

  void getNewPiece();
  void swapPiece();

 public:
  Game();
  ~Game();

  void init();

  Vec3d getCurrentPiecePos() const;

  const TetrisPiece3d* getCurrentPiece() const;

  void hardDrop(Board& board);
  int tryHold();

  void tryMoveX(int n);
  void tryMoveY(int n);

  void tryRotateXY(int r);
  void tryRotateXZ(int r);
  void tryRotateYZ(int r);
};