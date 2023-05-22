#include "board/board.hpp"

int textOffset = 10;

const Vec3d Board::sideN = {50, 0 - textOffset, 0};
const Vec3d Board::sideE = {100 + textOffset, 50, 0};
const Vec3d Board::sideS = {50, 100 + textOffset, 0};
const Vec3d Board::sideW = {0 - textOffset, 50, 0};

Board::Board() {}

void Board::init() {
  cubePositions.fill(0);

  for (int i = 0; i < 11; i++) {
    boardLines.push_back(Line({0, i * 10, 0}, {100, i * 10, 0}, Color::White));
  }

  for (int i = 0; i < 11; i++) {
    boardLines.push_back(Line({i * 10, 0, 0}, {i * 10, 100, 0}, Color::White));
  }

  int boardHeight = 200;

  boardLines.push_back(Line({0, 0, 0}, {0, 0, boardHeight}, Color::White));
  boardLines.push_back(Line({100, 0, 0}, {100, 0, boardHeight}, Color::White));
  boardLines.push_back(Line({0, 100, 0}, {0, 100, boardHeight}, Color::White));
  boardLines.push_back(
      Line({100, 100, 0}, {100, 100, boardHeight}, Color::White));
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

int Board::getHighestInColumnBelowValue(int x, int y, int z) const {
  for (int i = z - 1; i >= 0; i--) {
    if (hasCubeInPosition(x, y, i)) {
      return i;
    }
  }
  return -1;
}

void Board::handleDrop(const TetrisPiece3d *piece, const Vec3d &pos) {
  int highest = -1;

  std::vector<Vec3d> absPos = piece->getAbsolutePositions(pos);
  std::vector<Vec3d> relPos = piece->getRelativePositions();

  int relativeAdjustment = piece->getPieceLength();
  for (int i = 0; i < relPos.size(); i++) {
    int height = relPos[i].z;
    if (height < relativeAdjustment) {
      relativeAdjustment = height;
    }
  }

  for (const auto &v : absPos) {
    int columnHeight =
        getHighestInColumnBelowValue(v.x, v.y, v.z - relativeAdjustment);
    if (columnHeight > highest) {
      highest = columnHeight;
    }
  }

  for (int i = 0; i < absPos.size(); i++) {
    const Vec3d newPos = {absPos[i].x, absPos[i].y,
                          highest + 1 + relPos[i].z - relativeAdjustment};
    const Cube c = Cube(newPos, piece->getColor(), piece->getColor());
    addCube(newPos, c);
  }
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
