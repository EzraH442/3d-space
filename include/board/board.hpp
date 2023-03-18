#pragma once
#include <array>
#include <unordered_map>
#include "render/cube.hpp"

class Board {
  std::array<int, 10 * 10 * 20> cubePositions;
  std::unordered_map<int, Cube> cubes;

  public:
  Board();

  void addCube(int pos, Cube &c);
  void addCube(int x, int y, int z, Cube &c);
};