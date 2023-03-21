#pragma once

#include <vector>

class Bag {
  static int NUM_PIECES;
  std::vector<int> pieces;
  void refill();

 public:
  Bag();
  int getNextPieceId();
};