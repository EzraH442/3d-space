#pragma once

#include "board/bag.hpp"
#include "board/board.hpp"
#include "pieces/piece_factory.hpp"
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

  bool tryMove(const Vec3d& v, const Board& b);
  void tryRotate(const Vec3d& r, const Board& b);
};