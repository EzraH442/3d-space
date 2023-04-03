#include "game.hpp"

#include "pieces/abstract_tetris_piece.hpp"
#include "pieces/j_piece.hpp"
#include "pieces/tetris_piece.hpp"
#include "render/line.hpp"

Game::Game(){};

Game::~Game() { delete currentPiece; }

void Game::init() {
  currentPieceId = bag.getNextPieceId();
  currentPiece = tpf.createPiece(currentPieceId);
  currentHeldId = -1;
  currentPiecePos = {5, 5, 18};
  canHold = true;
}

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

const AbstractTetrisPiece3d* Game::getCurrentPiece() const {
  return currentPiece;
}

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

void Game::tryMoveX(int n) { currentPiecePos.x += n; }

void Game::tryMoveY(int n) { currentPiecePos.y += n; }

void Game::tryRotateXY(int r) { currentPiece->rotateXY(r); }

void Game::tryRotateXZ(int r) { currentPiece->rotateXZ(r); }

void Game::tryRotateYZ(int r) { currentPiece->rotateYZ(r); }