#include "board/bag.hpp"

#include <cstdlib>
#include <iostream>

int Bag::NUM_PIECES = 5;

// min inclusive, max exclusive
int randomBetween(int min, int max) { return (rand() % max - 1) + min; }

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
  int ret = pieces[index];
  pieces.erase(pieces.begin() + index);
  return ret;
}