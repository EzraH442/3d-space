#include "pieces/tetris_piece.hpp"

#include "pieces/piece_multiarray.hpp"

TetrisPiece3d::~TetrisPiece3d(){};
TetrisPiece3d::TetrisPiece3d() : dataArray(PieceMultiarray(3)){};
TetrisPiece3d::TetrisPiece3d(const Color &color, int length)
    : dataArray(PieceMultiarray(length)), color(color){};

void TetrisPiece3d::log() { dataArray.log(); }

std::vector<Vec3d> TetrisPiece3d::getAbsolutePositions(const Vec3d &pos) const {
  return dataArray.getAbsolutePositions(pos);
}

std::vector<Vec3d> TetrisPiece3d::getRelativePositions() const {
  return dataArray.getRelativePositions();
}

const Color TetrisPiece3d::getColor() const { return color; }

const int TetrisPiece3d::getPieceLength() const {
  return dataArray.getLength();
}

const PieceMultiarray TetrisPiece3d::getPieceMultiarray() const {
  return dataArray;
}

void TetrisPiece3d::rotateXY(int r) { dataArray.rotateXY(r); }
void TetrisPiece3d::rotateXZ(int r) { dataArray.rotateXZ(r); }
void TetrisPiece3d::rotateYZ(int r) { dataArray.rotateYZ(r); }
