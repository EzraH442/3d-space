#include <array>
#include "../render/cube.cpp"
#include <unordered_map>

class Board {
  std::array<int, 10 * 10 * 20> cubePositions;
  std::unordered_map<int, Cube> cubes;

  public:
  Board() {
    cubePositions.fill(0);
  }

  void addCube(int pos, Cube &c) {
    cubePositions[pos] = 1;
    cubes[pos] = c;
  }

  void addCube(int x, int y, int z, Cube &c) {
    cubePositions[x + 10 * y + 100 * z] = 1;
    cubes[x + 10 * y + 100 * z] = c;
  }
};