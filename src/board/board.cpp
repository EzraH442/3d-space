#include "board/board.hpp"

#include <unordered_map>
#include <utility>
#include <vector>

#include "render/cube.hpp"

Board::Board() {
  cubePositions.fill(0);

  Color black(0, 0, 0);

  for (int i = 0; i < 11; i++) {
    boardLines.push_back(Line({0, i * 10, 0}, {100, i * 10, 0}, black));
  }

  for (int i = 0; i < 11; i++) {
    boardLines.push_back(Line({i * 10, 0, 0}, {i * 10, 100, 0}, black));
  }

  int boardHeight = 200;

  boardLines.push_back(Line({0, 0, 0}, {0, 0, boardHeight}, black));
  boardLines.push_back(Line({100, 0, 0}, {100, 0, boardHeight}, black));
  boardLines.push_back(Line({0, 100, 0}, {0, 100, boardHeight}, black));
  boardLines.push_back(Line({100, 100, 0}, {100, 100, boardHeight}, black));
}

void Board::addCube(int pos, Cube &c) {
  cubePositions[pos] = 1;
  cubes.insert({1, c});
}

void Board::addCube(int x, int y, int z, Cube &c) {
  cubePositions[x + 10 * y + 100 * z] = 1;
  cubes.insert({1, c});
}

const std::unordered_map<int, Cube> Board::getCubes() const { return cubes; }

const std::vector<Line> Board::getLines() const { return boardLines; }

void Board::handleDrop(AbstractTetrisPiece3d *piece) {}