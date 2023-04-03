#include "board/bag.hpp"

#include <cstdlib>

int Bag::NUM_PIECES = 7;

// min inclusive, max exclusive
int randomBetween(int min, int max) { return (rand() % max - 1) + min + 1; }

Bag::Bag() { refill(); }

void Bag::refill() {
  for (int i = 0; i < NUM_PIECES; i++) {
    pieces.push_back(i);
  }
}

int Bag::getNextPieceId() {
  if (pieces.size() == 0) {
    refill();
  }

  int index = randomBetween(0, pieces.size());
  int ret = pieces.at(index);
  pieces.erase(pieces.begin() + index);
  return ret;
}