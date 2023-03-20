#include "color.hpp"

#include <iostream>

Color Color::Black = Color(0, 0, 0);
Color Color::White = Color(255, 255, 255);
Color Color::Cyan = Color(0, 255, 255);
Color Color::Blue = Color(0, 0, 255);
Color Color::Orange = Color(255, 127, 0);
Color Color::Yellow = Color(255, 255, 0);
Color Color::Green = Color(0, 255, 0);
Color Color::Purple = Color(128, 0, 128);
Color Color::Red = Color(255, 0, 0);

Color::Color() : r(255), g(255), b(255), a(255) {}

Color::Color(const Color& c) : r(c.r), g(c.g), b(c.b), a(c.a) {}

Color::Color(Uint8 r, Uint8 g, Uint8 b, Uint8 a) : r(r), g(g), b(b), a(a) {}

Color::Color(Uint8 r, Uint8 g, Uint8 b) : r(r), g(g), b(b), a(255) {
  std::cout << std::to_string(r) << "\n";
}
