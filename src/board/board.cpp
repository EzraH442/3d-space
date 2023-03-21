#include "board/board.hpp"

#include <iostream>
#include <unordered_map>
#include <utility>
#include <vector>

#include "color.hpp"
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

void Board::addCube(int pos, const Cube &c) {
  cubePositions[pos] = 1;
  cubes.insert({pos, c});
}

void Board::addCube(const Vec3d &pos, const Cube &c) {
  int position = pos.x + 10 * pos.y + 100 * pos.z;
  cubePositions[position] = 1;
  cubes.insert({position, c});
}

const std::unordered_map<int, Cube> Board::getCubes() const { return cubes; }

const std::vector<Line> Board::getLines() const { return boardLines; }

bool Board::hasCubeInPosition(int x, int y, int z) const {
  return cubePositions[x + y * 10 + z * 100];
}

int Board::getHighestInColumn(int x, int y) const {
  int highest = -1;
  for (int i = 19; i >= 0; i--) {
    if (hasCubeInPosition(x, y, i)) {
      highest = i;
    }
  }
  return highest;
}

void Board::handleDrop(const AbstractTetrisPiece3d *piece, const Vec3d &pos) {
  int highest = -1;

  std::vector<Vec3d> absPos = piece->getAbsolutePositions(pos);
  std::vector<Vec3d> relPos = piece->getRelativePositions();

  for (const auto &v : absPos) {
    int columnHeight = getHighestInColumn(v.x, v.y);
    if (columnHeight > highest) {
      highest = columnHeight;
    }
  }

  int relativeAdjustment = 3;
  for (int i = 0; i < relPos.size(); i++) {
    int height = relPos[i].z;
    if (height < relativeAdjustment) {
      relativeAdjustment = height;
    }
  }

  for (int i = 0; i < absPos.size(); i++) {
    const Vec3d newPos = {absPos[i].x, absPos[i].y,
                          highest + 1 + relPos[i].z - relativeAdjustment};
    const Cube c = Cube(newPos, Color::White, Color::Black);
    addCube(newPos, c);
  }
}