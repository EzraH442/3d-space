#include "include/color.h"
#include <algorithm>
#include <cctype>
#include <sstream>
#include <string>
#include <regex>
#include <sys/types.h>

Color::Color() {
  this->r = 0;
  this->g = 0;
  this->b = 0;
  this->a = 0;
}

Color::Color(u_int8_t r, u_int8_t g, u_int8_t b, u_int8_t a) {
  this->r = r;
  this->g = g;
  this->b = b;
  this->a = a;
}

Color::Color(u_int8_t r, u_int8_t g, u_int8_t b) {
  this->r = r;
  this->g = g;
  this->b = b;
  this->a = 255;
}

struct RGB {
  int r;
  int g;
  int b;
};

RGB hexToRGB(std::string s) {
  std::transform(s.begin(), s.end(), s.begin(), ::tolower);
  std::regex re("^#[a-f0-9]{6}");
  std::smatch m;
  std::regex_search(s, m, re);
  std::string match = m[0];
  uint v = std::stoul("0x"+match.substr(1, 6), nullptr, 16);
  
  int r = ((v >> 16) & 0xFF) / 255.0;
  int g = ((v >> 8) & 0xFF) / 255.0;
  int b = ((v) & 0xFF) / 255.0;

  return {r, g, b};
}

Color::Color(std::string s, u_int8_t a) {
  RGB rgb = hexToRGB(s);
  r = rgb.r;
  g = rgb.g;
  b = rgb.b;
  this->a = a;
}

Color::Color(std::string s) {
  RGB rgb = hexToRGB(s);
  r = rgb.r;
  g = rgb.g;
  b = rgb.b;
  this->a = 255;
}
