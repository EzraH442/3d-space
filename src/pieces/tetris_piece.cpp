#include "pieces/tetris_piece.hpp"

#include <vector>

#include "vector_3d.hpp"

TetrisPiece3D5::~TetrisPiece3D5(){};
TetrisPiece3D5::TetrisPiece3D5(){};

void TetrisPiece3D5::rotateXY(int r) { dataArray.rotateXY(r); }
void TetrisPiece3D5::rotateXZ(int r) { dataArray.rotateXZ(r); }
void TetrisPiece3D5::rotateYZ(int r) { dataArray.rotateYZ(r); }

void TetrisPiece3D5::log() { dataArray.log(); }

std::vector<Vec3d> TetrisPiece3D5::getAbsolutePositions(
    const Vec3d &pos) const {
  return dataArray.getAbsolutePositions(pos);
}

std::vector<Vec3d> TetrisPiece3D5::getRelativePositions() const {
  return dataArray.getRelativePositions();
}