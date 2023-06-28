#include "render/camera.hpp"

Camera::Camera(int boardLength) : defaultHeight(300), length(boardLength) {
  pos = {length / 2, length / 2, defaultHeight};
};

void Camera::move(const Vec3d &v) { pos = pos + v * 2; }

Vec3d Camera::getPos() const { return pos; }
