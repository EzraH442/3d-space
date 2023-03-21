#include "game.hpp"

#include "pieces/j_piece.hpp"
#include "pieces/tetris_piece.hpp"

Game::Game() {
  currentPieceId = bag.getNextPieceId();
  currentPiece = tpf.createPiece(currentPieceId);
  currentHeldId = -1;
  currentPiecePos = {0, 0, 18};
  canHold = true;
};

void Game::hardDrop(Board& b) {
  b.handleDrop(currentPiece);
  canHold = true;
  currentPieceId = bag.getNextPieceId();
}

Vec3d Game::getCurrentPiecePos() const { return currentPiecePos; }

int Game::tryHold() {
  if (currentHeldId == -1) {
    currentHeldId = currentPieceId;
    currentPieceId = bag.getNextPieceId();
    currentPiece = tpf.createPiece(currentPieceId);
    return 0;
  } else if (currentHeldId != 1 && canHold) {
    int temp = currentHeldId;
    currentHeldId = currentPieceId;
    currentPieceId = temp;
    currentPiece = tpf.createPiece(currentPieceId);
    return 1;
  } else {
    return 2;
  }
}