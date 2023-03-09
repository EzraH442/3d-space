#include "piece_multiarray.cpp"

class t_piece {
  PieceMultiarray dataArray = PieceMultiarray();

  public:
    t_piece() {
      dataArray.setFilled(0, 1, 0);
      dataArray.setFilled(1, 0, 0);
      dataArray.setFilled(1, 1, 0);
      dataArray.setFilled(2, 1, 0);
    }

    void rotateXY(int r) {
      // check if can rotate
      dataArray.logRaw();
      dataArray.rotateXY(r);
      dataArray.logRaw();
    }

    void rotateXZ(int r) {
      // check if can rotate
      dataArray.rotateXZ(r);
    }

    void rotateYZ(int r) {
      // check if can rotate
      dataArray.rotateYZ(r);
    }

    void log() {
      dataArray.log();
    }
};