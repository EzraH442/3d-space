#pragma once
#include <array>
#include <iostream>

class PieceMultiarray {

  std::array<bool, 27> data;

  public:
    PieceMultiarray() {
      data.fill(0);
    }

    void log() {
      std::cout << "--- piece\n";
      for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
          for (int k = 0; k < 3; k++) {
            std::cout << (isFilled(k, j, i) ? "*" : " ");
          }
          std::cout << "\n";
        }
        std::cout << "---\n";
      }
    }

    void logRaw() {
      std::cout << "--- piece\n";
      for (auto &i : data) {
        std::cout << i << " ";
      }
      std::cout << "\n";
    }

    bool isFilled(int x, int y, int z) {
      return data.at(x + y*3 + z*9);
    }

    bool isFilled(int n) {
      return data.at(n);
    }

    bool setFilled(int x, int y, int z, int filled=1) {
      return data.at(x + y*3 + z*9) = filled;
    }

    bool setFilled(int n, int filled) {
      return data.at(n) = filled;
    }

    void rotateXY(int r) {
      PieceMultiarray rotated = PieceMultiarray();

      if (r == 1) {
        for (int z = 0; z < 3; z++) {
          for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
              rotated.setFilled(2-j, i, z, isFilled(i, j, z));
            }
          }
        }
      } else {
        for (int z = 0; z < 3; z++) {
          for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
              rotated.setFilled(j, 2-i, z, isFilled(i, j, z));
            }
          }
        }
      }

      data = rotated.data;
    } 

    void rotateXZ(int r) {
      PieceMultiarray rotated = PieceMultiarray();

      if (r == 1) {
        for (int y = 0; y < 3; y++) {
          for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
              rotated.setFilled(2-j, y, i, isFilled(i, y, j));
            }
          }
        }
      } else {
        for (int y = 0; y < 3; y++) {
          for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
              rotated.setFilled(j, y, 2-i, isFilled(i, y, j));
            }
          }
        }
      }

      data = rotated.data;

    }

    void rotateYZ(int r) {
      PieceMultiarray rotated = PieceMultiarray();

      if (r == 1) {
        for (int x = 0; x < 3; x++) {
          for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
              rotated.setFilled(x, 2-j, i, isFilled(x, i ,j));
            }
          }
        }
      } else {
        for (int x = 0; x < 3; x++) {
          for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
              rotated.setFilled(x, j, 2-i, isFilled(x, i, j));
            }
          }
        }
      }

      data = rotated.data;

    }

};

