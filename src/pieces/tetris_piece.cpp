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

// each tetrinomino has 16 different rotation states: 4 in the XY plane, then
// for each one of those, 4 possible rotation states in the Z plane
// let 0, 4, 8, 12 be the 0th, 1st, 2nd, etc. clockwise rotations in XY
// let n+(0/1/2/3) be the 0/1/2/3 clockwise rotations in Z
// relative to the XY rotation

// first, consider rotations in the XY plane
// we will ignore any wall kicks that translate the piece in the Z plane
// therefore, the standard SRS wall kick table holds
// therefore: J, L, T, S, Z wall kick data for XY looks like this

//    rotation  |  test 1  |   test 2   |   test 3   |   test 4   |   test 5
//    -------------------------------------------------------------------------
//    0 -> 4    |  basic   | (-1, 0, 0) | (-1, 1, 0) | ( 0,-2, 0) | (-1,-2, 0)
//    4 -> 0    |  basic   | ( 1, 0, 0) | ( 1,-1, 0) | ( 0, 2, 0) | ( 1, 2, 0)
//    4 -> 8    |  basic   | ( 1, 0, 0) | ( 1,-1, 0) | ( 0, 2, 0) | ( 1, 2, 0)
//    8 -> 4    |  basic   | (-1, 0, 0) | (-1, 1, 0) | ( 0,-2, 0) | (-1,-2, 0)
//    8 -> 12   |  basic   | ( 1, 0, 0) | ( 1, 1, 0) | ( 0,-2, 0) | ( 1,-2, 0)
//    12 -> 8   |  basic   | (-1, 0, 0) | (-1,-1, 0) | ( 0, 2, 0) | (-1, 2, 0)
//    12 -> 0   |  basic   | (-1, 0, 0) | (-1,-1, 0) | ( 0, 2, 0) | (-1, 2, 0)
//    0 -> 12   |  basic   | ( 1, 0, 0) | ( 1, 1, 0) | ( 0,-2, 0) | ( 1,-2, 0)

// rotations in the XZ plane will be similar, except a rotation represents
// +/- 1 added to the rotation state number

// rotations in the YZ plane involve some tricky math
// rotation matrix for XY rotation
//  0 -1  0
//  1  0  0
//  0  0  1
// rotation matrix for XZ rotation
//  0  0 -1
//  0  1  0
//  1  0  0
// rotation matrix for YZ rotation
//  1  0  0
//  0  0 -1
//  0  1  0

// 1. try rotation
// 2. try translations in order, then rotate

// if canRotate do rotate()
// else
// for (each translation in translations) {
// translatedPiece = piece.move(translation)
// if translated.canRotate() do piece=translatedPiece, translatedPiece.rotate()
//}
void TetrisPiece3d::rotateXY(int r) { dataArray.rotateXY(r); }
void TetrisPiece3d::rotateXZ(int r) { dataArray.rotateXZ(r); }
void TetrisPiece3d::rotateYZ(int r) { dataArray.rotateYZ(r); }
