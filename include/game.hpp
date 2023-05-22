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
  Vec3d currentRotationState;

 public:
  Game();
  ~Game();

  void init();

  const Vec3d getCurrentPiecePos() const;
  const Vec3d getCurrentRotationState() const;

  const TetrisPiece3d* getCurrentPiece() const;

  void hardDrop(Board& board);
  int tryHold();

  void tryMove(const Vec3d& v, const Board& b);

  void tryRotateXY(int r, const Board& b);
  void tryRotateXZ(int r, const Board& b);
  void tryRotateYZ(int r, const Board& b);
};