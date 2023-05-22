#include "game.hpp"

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
  TetrisPiece3d* newPiece = tpf.createPiece(newPieceId);
  delete currentPiece;
  currentPiece = newPiece;
  currentPieceId = newPieceId;
  currentPiecePos = {5, 5, 18};
}

void Game::swapPiece() {
  int temp = currentHeldId;
  currentHeldId = currentPieceId;
  currentPieceId = temp;

  TetrisPiece3d* newPiece = tpf.createPiece(currentPieceId);
  delete currentPiece;
  currentPiece = newPiece;
}

void Game::hardDrop(Board& b) {
  b.handleDrop(currentPiece, currentPiecePos);
  canHold = true;

  getNewPiece();
}

Vec3d Game::getCurrentPiecePos() const { return currentPiecePos; }

const TetrisPiece3d* Game::getCurrentPiece() const { return currentPiece; }

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

void Game::tryMove(const Vec3d& v, const Board& board) {
  std::vector<Vec3d> newPiecePos =
      currentPiece->getAbsolutePositions(currentPiecePos + v);

  bool canMove = true;
  for (const Vec3d& pos : newPiecePos) {
    if (!board.isWithinBounds(pos) || board.hasCubeInPosition(pos)) {
      canMove = false;
    }
  }

  if (canMove) {
    currentPiecePos = currentPiecePos + v;
  }
}

void Game::tryRotateXY(int r) { currentPiece->rotateXY(r); }

void Game::tryRotateXZ(int r) { currentPiece->rotateXZ(r); }

void Game::tryRotateYZ(int r) { currentPiece->rotateYZ(r); }