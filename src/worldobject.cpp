#include "include/worldobject.h"

Color WorldObject::getColor() {
  return color;
}

void WorldObject::setColor(Color color) {
  this->color = color;
}

WorldObject::~WorldObject() {}