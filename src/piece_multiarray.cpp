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
      std::cout << "---\n";
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

    bool isFilled(int x, int y, int z) {
      return data.at(x + y*3 + z*9);
    }

    bool isFilled(int n) {
      return data.at(n);
    }

    bool setFilled(int x, int y, int z, int filled) {
      return data.at(x + y*3 + z*9) = filled;
    }

    bool setFilled(int n, int filled) {
      return data.at(n) = filled;
    }

    // r=1 -> clockwise, r=-1 -> counter-clockwise
    void rotateXY(int r) {
      PieceMultiarray rotated = PieceMultiarray();

      if (r == 1) {
        for (int i = 0; i < 3; i++) {
          for (int j = 0; j < 3; j++) {
            rotated.setFilled(2-j, i, 0, isFilled(i, j, 0));
          }
        }
      } else {
        for (int i = 0; i < 3; i++) {
          for (int j = 0; j < 3; j++) {
            rotated.setFilled(j, 2-i, 0, isFilled(i, j, 0));
          }
        }
      }

      data = rotated.data;
    } 

    void rotateXZ(int r) {

    }

    void rotateYZ(int r) {

    }

};

