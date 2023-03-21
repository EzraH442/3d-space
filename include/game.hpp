#pragma once

#include "board/bag.hpp"
#include "board/board.hpp"
#include "pieces/piece_factory.hpp"

class Game {
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

  AbstractTetrisPiece3d* currentPiece;

  Vec3d getCurrentPiecePos() const;

  void hardDrop(Board& board);
  int tryHold();

  void tryMoveX(int n);
  void tryMoveY(int n);

  void tryRotateXY(int r);
  void tryRotateXZ(int r);
  void tryRotateYZ(int r);
};