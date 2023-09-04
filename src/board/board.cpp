#include "board/board.hpp"

#include <algorithm>
#include <memory>
#include <unordered_map>

int textOffset = 10;

const Vec3d Board::sideN = {50, 100 + textOffset, 0};
const Vec3d Board::sideE = {0 - textOffset, 50, 0};
const Vec3d Board::sideS = {50, 0 - textOffset, 0};
const Vec3d Board::sideW = {100 + textOffset, 50, 0};

Board::Board() {}

void Board::init() {
  cubePositions.fill(0);

  for (int i = 0; i < 11; i++) {
    boardLines.push_back(
        Line(Vec3d{0, i * 10, 0}, Vec3d{100, i * 10, 0}, Color::White));
  }

  for (int i = 0; i < 11; i++) {
    boardLines.push_back(
        Line(Vec3d{i * 10, 0, 0}, Vec3d{i * 10, 100, 0}, Color::White));
  }

  int boardHeight = 200;

  boardLines.push_back(
      Line(Vec3d{0, 0, 0}, Vec3d{0, 0, boardHeight}, Color::White));
  boardLines.push_back(
      Line(Vec3d{100, 0, 0}, Vec3d{100, 0, boardHeight}, Color::White));
  boardLines.push_back(
      Line(Vec3d{0, 100, 0}, Vec3d{0, 100, boardHeight}, Color::White));
  boardLines.push_back(
      Line(Vec3d{100, 100, 0}, Vec3d{100, 100, boardHeight}, Color::White));
}

bool Board::addCube(int pos, const Cube &c) {
  if (pos >= 1900) {
    return false;
  }
  cubePositions[pos] = 1;
  cubes.insert({pos, c});
  return true;
}

bool Board::addCube(const Vec3d &pos, const Cube &c) {
  int position = pos.x + 10 * pos.y + 100 * pos.z;
  return addCube(position, c);
}

void Board::removeCube(int pos) {
  cubePositions[pos] = 0;
  cubes.erase(pos);
}

void Board::removeCube(const Vec3d &pos) {
  int position = pos.x + 10 * pos.y + 100 * pos.z;
  removeCube(position);
}
const std::map<int, Cube> Board::getCubes() const { return cubes; }

const std::vector<Line> Board::getLines() const { return boardLines; }

bool Board::hasCubeInPosition(int x, int y, int z) const {
  return cubePositions[x + y * 10 + z * 100];
}

bool Board::hasCubeInPosition(const Vec3d &v) const {
  return cubePositions[v.x + v.y * 10 + v.z * 100];
}

bool Board::isWithinBounds(const Vec3d &v) const {
  return (v.x >= 0 && v.x < 10) && (v.y >= 0 && v.y < 10) &&
         (v.z >= 0 && v.z < 20);
}

int Board::getHighestInColumnBelowValue(const Vec3d &v) const {
  int checkedZ = v.z - 1;

  while (!hasCubeInPosition(v.x, v.y, checkedZ) && checkedZ >= 0) {
    checkedZ--;
  }

  return checkedZ;
}

bool Board::handleDrop(const TetrisPiece3d *piece, const Vec3d &pos) {
  std::vector<Vec3d> absPos = piece->getAbsolutePositions(pos);

  std::unordered_map<int, Vec3d> downwardPositions;

  for (const auto &pos : absPos) {
    int index = pos.x + 10 * pos.y;

    if (downwardPositions.find(index) == downwardPositions.end() ||
        downwardPositions.at(index).z > pos.z) {
      downwardPositions.insert({index, pos});
    }
  }

  int minDown = 20;

  for (const auto &p : downwardPositions) {
    int distance = p.second.z - getHighestInColumnBelowValue(p.second);
    minDown = std::min(minDown, distance);
  }

  bool added = true;

  for (size_t i = 0; i < absPos.size(); i++) {
    int newZPos = absPos[i].z - minDown + 1;
    const Vec3d newPos = {absPos[i].x, absPos[i].y, newZPos};
    const Cube c = Cube(newPos, piece->getColor(), piece->getColor());
    added = added && addCube(newPos, c);
  }

  return added;
}

int Board::checkForClearedLines() {
  int score = 0;

  for (int i = 0; i < 20; i++) {
    for (int j = 0; j < 10; j++) {
      bool lineFull = true;
      for (int k = 0; k < 10; k++) {
        if (!hasCubeInPosition(j, k, i)) {
          lineFull = false;
          break;
        }
      }
      if (lineFull) {
        score += 1000;
        for (int k = 0; k < 10; k++) {
          removeCube(Vec3d{j, k, i});
        }
      }
    }
    for (int j = 0; j < 10; j++) {
      bool lineFull = true;
      for (int k = 0; k < 10; k++) {
        if (!hasCubeInPosition(k, j, i)) {
          lineFull = false;
          break;
        }
      }
      if (lineFull) {
        score += 1000;
        for (int k = 0; k < 10; k++) {
          removeCube(Vec3d{k, j, i});
        }
      }
    }
  }

  return score;
}

bool Board::isValidPiecePos(const std::vector<Vec3d> &pos) const {
  bool isValid = true;
  for (const Vec3d &p : pos) {
    if (!isWithinBounds(p) || hasCubeInPosition(p)) {
      isValid = false;
    }
  }
  return isValid;
}

void Board::clear() {
  cubePositions.fill(0);
  cubes.clear();
}