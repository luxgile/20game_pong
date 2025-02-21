#pragma once
#include "flecs.h"
#include "flecs/addons/cpp/world.hpp"
#include "raylib.h"
#include "raymath.h"

namespace common {

struct module {
  module(flecs::world &world);
};

/// Tag to reference the player.
struct Player {};

struct Position2D {
  Vector2 value;
};

struct Rectangle {
  float width;
  float height;
};

struct BaseColor {
  Color value;
};
}; // namespace Common


