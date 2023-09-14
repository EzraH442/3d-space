#pragma once

#include <memory>
#include <type_traits>

#include "board/bag.hpp"
#include "board/board.hpp"
#include "enums.hpp"
#include "pieces/piece_factory.hpp"
#include "pieces/tetris_piece.hpp"
#include "state/state.hpp"
#include "vector_2d.hpp"

// rotations in each plane will follow the standard SRS wallkick order

//    rotation  | test 1  | test 2  | test 3  | test 4  | test 5
//    ------------------------------------------------------------
//    0 -> 1    | ( 0, 0) | (-1, 0) | (-1, 1) | ( 0,-2) | (-1,-2)
//    1 -> 2    | ( 0, 0) | ( 1, 0) | ( 1,-1) | ( 0, 2) | ( 1, 2)
//    2 -> 3    | ( 0, 0) | ( 1, 0) | ( 1, 1) | ( 0,-2) | ( 1,-2)
//    3 -> 0    | ( 0, 0) | (-1, 0) | (-1,-1) | ( 0, 2) | (-1, 2)
//    0 -> 3    | ( 0, 0) | ( 1, 0) | ( 1, 1) | ( 0,-2) | ( 1,-2)
//    1 -> 0    | ( 0, 0) | ( 1, 0) | ( 1,-1) | ( 0, 2) | ( 1, 2)
//    2 -> 1    | ( 0, 0) | (-1, 0) | (-1, 1) | ( 0,-2) | (-1,-2)
//    3 -> 2    | ( 0, 0) | (-1, 0) | (-1,-1) | ( 0, 2) | (-1, 2)

const std::array<std::array<Vec2d<int>, 5>, 8> wallkicks = {{
    {{{0, 0}, {-1, 0}, {-1, 1}, {0, -2}, {-1, -2}}},
    {{{0, 0}, {1, 0}, {1, -1}, {0, 2}, {1, 2}}},
    {{{0, 0}, {1, 0}, {1, 1}, {0, -2}, {1, -2}}},
    {{{0, 0}, {-1, 0}, {-1, -1}, {0, 2}, {-1, 2}}},
    {{{0, 0}, {1, 0}, {1, 1}, {0, -2}, {1, -2}}},
    {{{0, 0}, {1, 0}, {1, -1}, {0, 2}, {1, 2}}},
    {{{0, 0}, {-1, 0}, {-1, 1}, {0, -2}, {-1, -2}}},
    {{{0, 0}, {-1, 0}, {-1, -1}, {0, 2}, {-1, 2}}},
}};

class Game {
  std::unique_ptr<TetrisPiece3d> currentPiece;
  Bag bag;
  PieceType currentPieceId;
  PieceType currentHeldId;
  bool currentlyHolding;
  bool canHold;
  Vec3d currentPiecePos;
  TetrisPieceFactory tpf;

  void getNewPiece();
  void swapPiece();
  Vec3d currentRotationState;

  int score;

 public:
  Game();
  ~Game();

  void init();
  void reset();

  int getScore() const;
  const Vec3d getCurrentPiecePos() const;
  const Vec3d getCurrentRotationState() const;
  PieceType getHeldPiece() const;
  bool isHolding() const;

  const TetrisPiece3d* getCurrentPiece() const;

  void hardDrop(Board& board, StateMachine& m);
  int tryHold();

  bool tryMove(const Vec3d& v, const Board& b);
  void tryRotate(const Vec3d& r, const Board& b);
};