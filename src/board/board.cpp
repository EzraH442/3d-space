#include "board/board.hpp"

Board::Board() {
  cubePositions.fill(0);
}

void Board::addCube(int pos, Cube &c) {
  cubePositions[pos] = 1;
  cubes[pos] = c;
}

void Board::addCube(int x, int y, int z, Cube &c) {
  cubePositions[x + 10 * y + 100 * z] = 1;
  cubes[x + 10 * y + 100 * z] = c;
}