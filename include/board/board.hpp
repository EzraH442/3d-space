#pragma once

#include <map>

#include "pieces/tetris_piece.hpp"
#include "render/cube.hpp"
#include "vector_3d.hpp"

class Board {
  std::vector<Drawable const *> boardLines;
  std::array<int, 10 * 10 * 20> cubePositions;
  std::map<int, Cube> cubes;

  int getHighestInColumnBelowValue(const Vec3d &v) const;
  bool hasCubeInPosition(int x, int y, int z) const;
  bool hasCubeInPosition(const Vec3d &position) const;
  bool isWithinBounds(const Vec3d &position) const;

  bool addCube(int pos, const Cube &c);
  bool addCube(const Vec3d &pos, const Cube &c);
  void removeCube(int pos);
  void removeCube(const Vec3d &pos);

 public:
  const static Vec3d sideN;
  const static Vec3d sideE;
  const static Vec3d sideS;
  const static Vec3d sideW;
  Board();
  ~Board();

  void init();

  bool handleDrop(const TetrisPiece3d *piece, const Vec3d &pos);

  const std::map<int, Cube> getCubes() const;
  const std::vector<Drawable const *> getLines() const;
  int checkForClearedLines();

  bool isValidPiecePos(const std::vector<Vec3d> &pos) const;
};