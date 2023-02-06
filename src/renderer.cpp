#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include "include/sphere.h"

struct Camera {
  Vec3d pos;
  Angle3d rot;
};
