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
  currentRotationState = {0, 0, 0};
  canHold = true;
}

void Game::getNewPiece() {
  int newPieceId = bag.getNextPieceId();
  TetrisPiece3d* newPiece = tpf.createPiece(newPieceId);
  delete currentPiece;
  currentPiece = newPiece;
  currentPieceId = newPieceId;
  currentPiecePos = {5, 5, 18};
  currentRotationState = {0, 0, 0};
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

const Vec3d Game::getCurrentPiecePos() const { return currentPiecePos; }
const Vec3d Game::getCurrentRotationState() const {
  return currentRotationState;
}

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

  if (board.isValidPiecePos(newPiecePos)) {
    currentPiecePos = currentPiecePos + v;
  }
}

// rotations in each plane will follow the standard SRS wallkick order

//    rotation  | test 1  | test 2  | test 3  | test 4  | test 5
//    ------------------------------------------------------------
//    0 -> 1    | ( 0, 0) | (-1, 0) | (-1, 1) | ( 0,-2) | (-1,-2)
//    1 -> 2    | ( 0, 0) | ( 1, 0) | ( 1,-1) | ( 0, 2) | ( 1, 2)
//    2 -> 3    | ( 0, 0) | ( 1, 0) | ( 1, 1) | ( 0,-2) | ( 1,-2)
//    3 -> 0    | ( 0, 0) | (-1, 0) | (-1,-1) | ( 0, 2) | (-1, 2)
//    0 -> 3    | ( 0, 0) | ( 1, 0) | ( 1, 1) | ( 0,-2) | ( 1,-2)
//    1 -> 0    | ( 0, 0) | ( 1, 0) | ( 1,-1) | ( 0, 2) | ( 1, 2)
//    2 -> 1    | ( 0, 0) | (-1, 0) | (-1, 1) | ( 0,-2) | (-1,-2)
//    3 -> 2    | ( 0, 0) | (-1, 0) | (-1,-1) | ( 0, 2) | (-1, 2)

struct Vec2d {
  int x, y;
};

std::array<const std::array<const Vec2d, 5>, 8> wallkicks = {{
    {{{0, 0}, {-1, 0}, {-1, 1}, {0, -2}, {-1, -2}}},
    {{{0, 0}, {1, 0}, {1, -1}, {0, 2}, {1, 2}}},
    {{{0, 0}, {1, 0}, {1, 1}, {0, -2}, {1, -2}}},
    {{{0, 0}, {-1, 0}, {-1, -1}, {0, 2}, {-1, 2}}},
    {{{0, 0}, {1, 0}, {1, 1}, {0, -2}, {1, -2}}},
    {{{0, 0}, {1, 0}, {1, -1}, {0, 2}, {1, 2}}},
    {{{0, 0}, {-1, 0}, {-1, 1}, {0, -2}, {-1, -2}}},
    {{{0, 0}, {-1, 0}, {-1, -1}, {0, 2}, {-1, 2}}},
}};

void Game::tryRotateXY(int r, const Board& b) {
  bool positive = r > 0;
  int wallkickIndex =
      (positive) ? currentRotationState.x : currentRotationState.x + 4;

  PieceMultiarray pm = PieceMultiarray(currentPiece->getPieceMultiarray());
  pm.rotateXY(r);

  // attempt all 5 posssible wallkicks in order
  for (int i = 0; i < 5; i++) {
    Vec2d wk = wallkicks[wallkickIndex][i];
    std::cout << "attempting translation " << wk.x << ", " << wk.y << "\n";
    Vec3d rotPos = currentPiecePos + Vec3d{wk.x, wk.y, 0};

    if (b.isValidPiecePos(pm.getAbsolutePositions(rotPos))) {
      currentPiece->rotateXY(r);
      std::cout << "found rotation \n";

      int x = currentRotationState.x;
      currentRotationState.x = (positive) ? (x + 1) % 4 : (x + 3) % 4;
      currentPiecePos = rotPos;
      return;
    }
  }
}

void Game::tryRotateXZ(int r, const Board& b) { currentPiece->rotateXZ(r); }

void Game::tryRotateYZ(int r, const Board& b) { currentPiece->rotateYZ(r); }