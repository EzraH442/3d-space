#include "pieces/tetris_piece.h"

void AbstractTetrisPiece3D::rotateXY(int r) {
  dataArray.rotateXY(r);
}

void AbstractTetrisPiece3D::rotateXZ(int r) {
  dataArray.rotateXZ(r);
}

void AbstractTetrisPiece3D::rotateYZ(int r) {
  dataArray.rotateYZ(r);
}

void AbstractTetrisPiece3D::log() {
  dataArray.log();
}