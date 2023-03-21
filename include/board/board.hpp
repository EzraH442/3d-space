#pragma once

#include <array>
#include <unordered_map>
#include <utility>
#include <vector>

#include "pieces/abstract_tetris_piece.hpp"
#include "pieces/tetris_piece.hpp"
#include "render/cube.hpp"

class Board {
  std::vector<Line> boardLines;
  std::array<int, 10 * 10 * 20> cubePositions;
  std::unordered_map<int, Cube> cubes;

  int getHighestInColumn(int x, int y) const;

  bool hasCubeInPosition(int x, int y, int z) const;

 public:
  Board();

  void addCube(int pos, const Cube &c);
  void addCube(const Vec3d &pos, const Cube &c);

  void handleDrop(const AbstractTetrisPiece3d *piece, const Vec3d &pos);

  const std::unordered_map<int, Cube> getCubes() const;
  const std::vector<Line> getLines() const;
};