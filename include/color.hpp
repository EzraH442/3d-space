#pragma once

#include <string>

#include "SDL_stdinc.h"

class Color {
 public:
  static const Color White;
  static const Color Black;
  static const Color Cyan;
  static const Color Blue;
  static const Color Orange;
  static const Color Yellow;
  static const Color Green;
  static const Color Purple;
  static const Color Red;

  const Uint8 r, g, b, a;

  Color();
  Color(const Color&);
  Color(Uint8 r, Uint8 g, Uint8 b, Uint8 a);
  Color(Uint8 r, Uint8 g, Uint8 b);
};