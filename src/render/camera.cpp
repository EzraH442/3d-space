#include "render/camera.hpp"

Camera::Camera(){};

void Camera::changeHeight(int n) {
  if (height + n <= 300 || height + n >= 500) return;
  height += n;
}

void Camera::changeOffset(int n) {
  if (offset + n <= 0 || offset + n >= 100) return;
  offset += n;
}

int Camera::getHeight() const { return height; }

int Camera::getOffset() const { return offset; }

Vec3d Camera::getPos(int dir) const {
  return {length + offset, length + offset, height};
}
