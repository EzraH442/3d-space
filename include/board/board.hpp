#pragma once

#include <array>
#include <map>
#include <vector>

#include "pieces/tetris_piece.hpp"
#include "render/cube.hpp"

class Board {
  std::vector<Line> boardLines;
  std::array<int, 10 * 10 * 20> cubePositions;
  std::map<int, Cube> cubes;

  int getHighestInColumn(int x, int y) const;

 public:
  const static Vec3d sideN;
  const static Vec3d sideE;
  const static Vec3d sideS;
  const static Vec3d sideW;
  Board();

  void init();

  void addCube(int pos, const Cube &c);
  void addCube(const Vec3d &pos, const Cube &c);

  void handleDrop(const TetrisPiece3d *piece, const Vec3d &pos);

  const std::map<int, Cube> getCubes() const;
  const std::vector<Line> getLines() const;

  bool hasCubeInPosition(int x, int y, int z) const;
  bool hasCubeInPosition(const Vec3d &position) const;
  bool isWithinBounds(const Vec3d &position) const;
};