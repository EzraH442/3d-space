#include <vector_3d.hpp>

class Camera {
  int height = 500;
  int length = 100; // total length of "board / playing area"
  int offset = 100;

  public:
  
    Camera() {};

    void changeHeight(int n) {
      if (height + n <= 300 || height + n >= 600) return;
      height += n;
    }

    void changeOffset(int n) {
      offset += n;
    }

    Vec3d getPos(int dir) {
      if (dir == 0) return {length + offset, length + offset, height};
      else if (dir == 1) return {0 - offset, length + offset, height};
      else if (dir == 2) return {0 - offset, 0 - offset, height};
      else if (dir == 3) return {length + offset, 0 - offset, height};
      else {
        std::cout << "bad direction: " << dir << "\n";
        return {length + offset, length + offset, height};
      }
    }
};