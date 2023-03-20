#pragma once

#include <string>

#include "SDL_stdinc.h"

struct Color {
  static Color White;
  static Color Black;
  static Color Cyan;
  static Color Blue;
  static Color Orange;
  static Color Yellow;
  static Color Green;
  static Color Purple;
  static Color Red;

  uint8_t r, g, b, a;

  Color();
  Color(Uint8 r, Uint8 g, Uint8 b, Uint8 a);
  Color(Uint8 r, Uint8 g, Uint8 b);
};