#pragma once

#include <vector>

#include "enums.hpp"

class Bag {
  static int NUM_PIECES;
  std::vector<PieceType> pieces;
  void refill();

 public:
  Bag();
  PieceType getNextPieceType();
};