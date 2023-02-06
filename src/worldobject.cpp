#include "include/worldobject.h"

sf::Color WorldObject::getColor() {
  return color;
}

void WorldObject::setColor(sf::Color color) {
  this->color = color;
}

WorldObject::~WorldObject() {}