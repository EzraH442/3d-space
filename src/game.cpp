#include "game.hpp"

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
  bool success = b.handleDrop(currentPiece, currentPiecePos);
  int score = b.checkForClearedLines();

  if (!success) {
    // lose
    std::cout << "lose\n";
  }

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

bool Game::tryMove(const Vec3d& v, const Board& board) {
  std::vector<Vec3d> newPiecePos =
      currentPiece->getAbsolutePositions(currentPiecePos + v);

  bool isValid = board.isValidPiecePos(newPiecePos);

  if (isValid) {
    currentPiecePos = currentPiecePos + v;
  }

  return isValid;
}

// vector r encodes information about which axis to rotate around and the
// direction to rotate, assumes rotation of 90 degrees always

void Game::tryRotate(const Vec3d& r, const Board& b) {
  bool positive = (r.x + r.y + r.z) > 0;
  int rotation = positive ? 1 : -1;

  int X_AXIS = 0;
  int Y_AXIS = 1;
  int Z_AXIS = 2;

  int axis;

  if (r.x != 0) {
    axis = X_AXIS;
  } else if (r.y != 0) {
    axis = Y_AXIS;
  } else if (r.z != 0) {
    axis = Z_AXIS;
  } else {
    std::cout << "bad axis";
    axis = 0;
  }

  Vec3d wallkickIndices =
      (positive) ? currentRotationState : currentRotationState + Vec3d{4, 4, 4};

  PieceMultiarray pm = PieceMultiarray(currentPiece->getPieceMultiarray());

  std::array<Vec2d<int>, 5> wks;

  if (axis == X_AXIS) {
    pm.rotateYZ(rotation);
    wks = wallkicks[wallkickIndices.x];
  } else if (axis == Y_AXIS) {
    pm.rotateXZ(rotation);
    wks = wallkicks[wallkickIndices.y];
  } else if (axis == Z_AXIS) {
    pm.rotateXY(rotation);
    wks = wallkicks[wallkickIndices.z];
  }

  // attempt all 5 posssible wallkicks in order
  for (int i = 0; i < 5; i++) {
    Vec2d<int> wk = wks[i];

    Vec3d translationVector;

    if (axis == X_AXIS) {
      translationVector = {0, wk.x, wk.y};
    } else if (axis == Y_AXIS) {
      translationVector = {wk.x, 0, wk.y};
    } else if (axis == Z_AXIS) {
      translationVector = {wk.x, wk.y, 0};
    }

    Vec3d rotatedPosition = currentPiecePos + translationVector;

    if (b.isValidPiecePos(pm.getAbsolutePositions(rotatedPosition))) {
      if (axis == X_AXIS) {
        currentPiece->rotateYZ(rotation);
      } else if (axis == Y_AXIS) {
        currentPiece->rotateXZ(rotation);
      } else if (axis == Z_AXIS) {
        currentPiece->rotateXY(rotation);
      }

      currentRotationState = Vec3d{(currentRotationState.x + r.x + 4) % 4,
                                   (currentRotationState.y + r.z + 4) % 4,
                                   (currentRotationState.z + r.z + 4) % 4};
      currentPiecePos = rotatedPosition;
      return;
    }
  }
}