#include <include/sphere.h>
#include <include/color.h>

Sphere::~Sphere() { }

void Sphere::move(Vec3d newPos) {
  this->position = newPos;
}

void Sphere::rotate(Vec3d newDir) {
  this->direction = newDir;
}

Sphere::Sphere(int radius) {
  this->radius = radius;
  position = {0,0,0};
  direction = {0,0,0};
  color = Color(0,0,0);
}

Sphere::Sphere(Vec3d pos, int radius) {
  this->radius = radius;
  position = pos;
  direction = {0,0,0};
  color = Color(0,0,0);
}

Sphere::Sphere(Vec3d pos, int radius, Vec3d dir) {
  this->radius = radius;
  position = pos;
  direction = dir;
  color = Color(0,0,0);
}
