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

 public:
  Board();

  void addCube(int pos, Cube &c);
  void addCube(int x, int y, int z, Cube &c);
  void handleDrop(AbstractTetrisPiece3d *piece);
  const std::unordered_map<int, Cube> getCubes() const;
  const std::vector<Line> getLines() const;
};