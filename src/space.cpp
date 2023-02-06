#include <SFML/Graphics/Color.hpp>
#include <vector>
#include "structs.cpp"
#include <SFML/Graphics.hpp>

class Point {
  public:
  Vec3d pos;
  sf::Color color;
  Point(Vec3d pos, sf::Color color);
};

class Space {
  public:
  std::vector<Point> v = {};
};