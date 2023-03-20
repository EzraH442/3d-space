#include "board/board.hpp"
#include "render/cube.hpp"
#include <utility>
#include <vector>

Board::Board() {
  cubePositions.fill(0);

  for (int i = 0; i < 11; i++) {
    boardLines.push_back(Line({0,i*10,0}, {100,i*10,0}));
  }

  for (int i = 0; i < 11; i++) {
    boardLines.push_back(Line({i*10, 0 ,0}, {i*10, 100, 0}));
  }

  int boardHeight = 200;

  boardLines.push_back(Line({0,0,0}, {0,0,boardHeight}));
  boardLines.push_back(Line({100,0,0}, {100,0,boardHeight}));
  boardLines.push_back(Line({0,100,0}, {0,100,boardHeight}));
  boardLines.push_back(Line({100,100,0}, {100,100,boardHeight}));
}

void Board::addCube(int pos, Cube &c) {
  cubePositions[pos] = 1;
  cubes[pos] = c;
}

void Board::addCube(int x, int y, int z, Cube &c) {
  cubePositions[x + 10 * y + 100 * z] = 1;
  cubes[x + 10 * y + 100 * z] = c;
}

std::vector<std::pair<Vec3d, Cube>> Board::getCubes() const {
  std::vector<std::pair<Vec3d, Cube>> ret(cubes.size());

  for(auto const& pair : cubes) {
    ret.push_back( {
      {pair.first % 10, (pair.first / 10) % 10, pair.first / 100}, 
      pair.second
    });
  }

  return ret;
}

std::vector<Line> Board::getLines() const {
  return boardLines;
}