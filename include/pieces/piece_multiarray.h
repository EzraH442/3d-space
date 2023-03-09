#pragma once
#include <array>
#include <iostream>

class PieceMultiarray {

  std::array<bool, 27> data;

  public:
    PieceMultiarray();

    void log(); 
    void logRaw();

    bool isFilled(int x, int y, int z);
    bool isFilled(int n); 
    bool setFilled(int x, int y, int z, int filled = 1);
    bool setFilled(int n, int filled = 1); 

    void rotateXY(int r);
    void rotateXZ(int r);
    void rotateYZ(int r);
};

