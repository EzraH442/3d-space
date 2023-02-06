#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Color.hpp>
#include <iostream>
#include "src/renderer.cpp"
#include "include/sphere.h"

void renderPointEzra(sf::RenderWindow& window, Sphere s) {
  sf::CircleShape shape(20.0f);
  shape.setFillColor(s.getColor());
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 800), "SFML works!");
    Sphere s({10, 10, 10}, 4);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();

        renderPointEzra(window, s);
        window.display();

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            std::cout << "hello";
        }
    }

    return 0;
}
