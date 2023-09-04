#include "pieces/piece_multiarray.hpp"

#include "vector_3d.hpp"

PieceMultiarray::PieceMultiarray() : length(0) {}
PieceMultiarray::PieceMultiarray(int length) : length(length) {
  std::vector<bool> v(length * length * length, 0);
  data = v;
}

void PieceMultiarray::log() {
  std::cout << "--- piece\n";
  for (int i = 0; i < length; i++) {
    for (int j = 0; j < length; j++) {
      for (int k = 0; k < length; k++) {
        std::cout << (isFilled(k, j, i) ? "*" : " ");
      }
      std::cout << "\n";
    }
    std::cout << "---\n";
  }
}

void PieceMultiarray::logRaw() {
  std::cout << "--- piece\n";
  for (const auto &i : data) {
    std::cout << i << " ";
  }
  std::cout << "\n";
}

const int PieceMultiarray::getLength() const { return length; }

bool PieceMultiarray::isFilled(int x, int y, int z) const {
  return data.at(x + y * length + z * length * length);
}

bool PieceMultiarray::isFilled(int n) const { return data.at(n); }

bool PieceMultiarray::setFilled(int x, int y, int z, int filled) {
  return data.at(x + y * length + z * length * length) = filled;
}

bool PieceMultiarray::setFilled(int n, int filled) {
  return data.at(n) = filled;
}

void PieceMultiarray::rotateXY(int r) {
  PieceMultiarray rotated = PieceMultiarray(length);

  if (r == 1) {
    for (int z = 0; z < length; z++) {
      for (int i = 0; i < length; i++) {
        for (int j = 0; j < length; j++) {
          rotated.setFilled(length - 1 - j, i, z, isFilled(i, j, z));
        }
      }
    }
  } else {
    for (int z = 0; z < length; z++) {
      for (int i = 0; i < length; i++) {
        for (int j = 0; j < length; j++) {
          rotated.setFilled(j, length - 1 - i, z, isFilled(i, j, z));
        }
      }
    }
  }

  data = rotated.data;
}

void PieceMultiarray::rotateXZ(int r) {
  PieceMultiarray rotated = PieceMultiarray(length);

  if (r == 1) {
    for (int y = 0; y < length; y++) {
      for (int i = 0; i < length; i++) {
        for (int j = 0; j < length; j++) {
          rotated.setFilled(length - 1 - j, y, i, isFilled(i, y, j));
        }
      }
    }
  } else {
    for (int y = 0; y < length; y++) {
      for (int i = 0; i < length; i++) {
        for (int j = 0; j < length; j++) {
          rotated.setFilled(j, y, length - 1 - i, isFilled(i, y, j));
        }
      }
    }
  }

  data = rotated.data;
}

void PieceMultiarray::rotateYZ(int r) {
  PieceMultiarray rotated = PieceMultiarray(length);

  if (r == 1) {
    for (int x = 0; x < length; x++) {
      for (int i = 0; i < length; i++) {
        for (int j = 0; j < length; j++) {
          rotated.setFilled(x, length - 1 - j, i, isFilled(x, i, j));
        }
      }
    }
  } else {
    for (int x = 0; x < length; x++) {
      for (int i = 0; i < length; i++) {
        for (int j = 0; j < length; j++) {
          rotated.setFilled(x, j, length - 1 - i, isFilled(x, i, j));
        }
      }
    }
  }

  data = rotated.data;
}

std::vector<Vec3d> PieceMultiarray::getAbsolutePositions(
    const Vec3d &pos) const {
  std::vector<Vec3d> ret;

  for (size_t i = 0; i < data.size(); i++) {
    if (isFilled(i)) {
      ret.push_back(Vec3d({static_cast<int>(i % length),
                           static_cast<int>((i / length) % length),
                           static_cast<int>(i / (length * length))}) +
                    pos);
    }
  }

  return ret;
}
