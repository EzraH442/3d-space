#pragma once

#include <SFML/Graphics.hpp>
#include "./structs.cpp"

class WorldObject {

  protected:
    sf::Color color;
  public:

  virtual ~WorldObject() = 0;
  virtual void move(Vec3d newPos) = 0;
  virtual void rotate(Vec3d newDir) = 0;

  sf::Color getColor();
  void setColor(sf::Color color);
};