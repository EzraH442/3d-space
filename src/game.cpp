#include "game.hpp"

#include "pieces/abstract_tetris_piece.hpp"
#include "pieces/j_piece.hpp"
#include "pieces/tetris_piece.hpp"
#include "render/line.hpp"

Game::Game() {
  currentPieceId = bag.getNextPieceId();
  currentPiece = tpf.createPiece(currentPieceId);
  currentHeldId = -1;
  currentPiecePos = {5, 5, 18};
  canHold = true;
};

Game::~Game() { delete currentPiece; }

void Game::getNewPiece() {
  int newPieceId = bag.getNextPieceId();
  AbstractTetrisPiece3d* newPiece = tpf.createPiece(newPieceId);
  delete currentPiece;
  currentPiece = newPiece;
  currentPieceId = newPieceId;
}

void Game::swapPiece() {
  int temp = currentHeldId;
  currentHeldId = currentPieceId;
  currentPieceId = temp;

  AbstractTetrisPiece3d* newPiece = tpf.createPiece(currentPieceId);
  delete currentPiece;
  currentPiece = newPiece;
}

void Game::hardDrop(Board& b) {
  b.handleDrop(currentPiece, currentPiecePos);
  canHold = true;

  getNewPiece();
}

Vec3d Game::getCurrentPiecePos() const { return currentPiecePos; }

int Game::tryHold() {
  if (currentHeldId == -1) {
    currentHeldId = currentPieceId;

    getNewPiece();

    return 0;
  } else if (currentHeldId != 1 && canHold) {
    swapPiece();
    return 1;
  } else {
    return 2;
  }
}