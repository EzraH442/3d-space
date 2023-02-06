#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include "space.cpp"

struct Camera {
  Vec3d pos;
  Angle3d rot;
};

void renderPointEzra(sf::RenderWindow& window, Point p) {
  sf::CircleShape shape(20.0f);
  shape.setFillColor(p.color);
}