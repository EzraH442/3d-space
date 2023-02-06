#include <include/cylinder.h>

void Cylinder::move(Vec3d newPos) {
  this->position = newPos;
}

void Cylinder::rotate(Vec3d newDir) {
  this->direction = newDir;
}