#include "game.hpp"

#include "enums.hpp"
#include "state/end_state.hpp"
#include "state/machine.hpp"
#include "state/menu_state.hpp"
#include "state/state.hpp"

Game::Game(){};

Game::~Game() {}

void Game::reset() {
  bag.reset();
  score = 0;
  currentlyHolding = false;
  currentPieceId = bag.getNextPieceType();
  currentPiece = tpf.createPiece(currentPieceId);
  currentPiecePos = {5, 5, 18};
  currentRotationState = {0, 0, 0};
  canHold = true;
}

void Game::init() {
  currentPieceId = bag.getNextPieceType();
  currentPiece = tpf.createPiece(currentPieceId);
  currentlyHolding = false;
  currentPiecePos = {5, 5, 18};
  currentRotationState = {0, 0, 0};
  canHold = true;
}

void Game::getNewPiece() {
  PieceType newPieceType = bag.getNextPieceType();
  currentPiece.reset(tpf.createPiece(newPieceType).release());
  currentPieceId = newPieceType;
  currentPiecePos = {5, 5, 18};
  currentRotationState = {0, 0, 0};
}

void Game::swapPiece() {
  PieceType temp = currentHeldId;
  currentHeldId = currentPieceId;
  currentPieceId = temp;

  currentPiece.reset(tpf.createPiece(currentPieceId).release());
}

void Game::hardDrop(Board& b, StateMachine& m) {
  bool success = b.handleDrop(currentPiece.get(), currentPiecePos);
  score += b.checkForClearedLines();

  if (!success) {
    m.score = score;
    m.changeState(EndState::getInstance(m));
  }

  canHold = true;
  getNewPiece();
}

const Vec3d Game::getCurrentPiecePos() const { return currentPiecePos; }
const Vec3d Game::getCurrentRotationState() const {
  return currentRotationState;
}

const TetrisPiece3d* Game::getCurrentPiece() const {
  return currentPiece.get();
}

int Game::tryHold() {
  if (!currentlyHolding) {
    currentHeldId = currentPieceId;

    getNewPiece();

    return 0;
  } else if (!currentlyHolding && canHold) {
    currentlyHolding = true;
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

  Axes axis;

  if (r.x != 0) {
    axis = Axes::X;
  } else if (r.y != 0) {
    axis = Axes::Y;
  } else if (r.z != 0) {
    axis = Axes::Z;
  } else {
    axis = Axes::X;
  }

  Vec3d wallkickIndices =
      (positive) ? currentRotationState : currentRotationState + Vec3d{4, 4, 4};

  PieceMultiarray pm = PieceMultiarray(currentPiece->getPieceMultiarray());

  std::array<Vec2d<int>, 5> wks;

  switch (axis) {
    case Axes::X: {
      pm.rotateYZ(rotation);
      wks = wallkicks[wallkickIndices.x];
    }
    case Axes::Y: {
      pm.rotateXZ(rotation);
      wks = wallkicks[wallkickIndices.y];
    }
    case Axes::Z: {
      pm.rotateXY(rotation);
      wks = wallkicks[wallkickIndices.z];
    }
  }

  // attempt all 5 posssible wallkicks in order

  for (const auto& wk : wks) {
    Vec3d translationVector;
    switch (axis) {
      case Axes::X:
        translationVector = {0, wk.x, wk.y};
        break;
      case Axes::Y:
        translationVector = {wk.x, 0, wk.y};
        break;
      case Axes::Z:
        translationVector = {wk.x, wk.y, 0};
    }

    Vec3d rotatedPosition = currentPiecePos + translationVector;

    if (b.isValidPiecePos(pm.getAbsolutePositions(rotatedPosition))) {
      switch (axis) {
        case Axes::X:
          currentPiece->rotateYZ(rotation);
          break;
        case Axes::Y:
          currentPiece->rotateXZ(rotation);
          break;
        case Axes::Z:
          currentPiece->rotateXY(rotation);
          break;
      }

      currentRotationState = Vec3d{(currentRotationState.x + r.x + 4) % 4,
                                   (currentRotationState.y + r.z + 4) % 4,
                                   (currentRotationState.z + r.z + 4) % 4};
      currentPiecePos = rotatedPosition;
      return;
    }
  }
}

int Game::getScore() const { return score; }

PieceType Game::getHeldPiece() const { return currentHeldId; }
bool Game::isHolding() const { return currentlyHolding; }