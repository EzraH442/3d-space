#pragma once

#include <cstdint>
#include <string>

class Color {
  private:
  uint8_t r;
  uint8_t g;
  uint8_t b;
  uint8_t a;

  public:
  Color();
  Color(uint8_t, uint8_t, uint8_t, uint8_t);
  Color(uint8_t, uint8_t, uint8_t);
  Color(std::string s);
  Color(std::string s, uint8_t a);

};