#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Color.hpp>
#include <iostream>
#include "renderer.cpp"

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 800), "SFML works!");
    Point p({10, 10, 10}, sf::Color::Blue);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();

        renderPointEzra(window, p);
        window.display();

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            std::cout << "hello";
        }
    }

    return 0;
}
