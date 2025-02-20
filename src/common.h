#pragma once
#include "flecs.h"
#include "raylib.h"
#include "raymath.h"

namespace Common {
struct CPlayer {};

struct CPosition {
  Vector2 value;
};

struct CRectangle {
  Color color;
  float width;
  float height;
};

void setup_systems(flecs::world &world);
}; // namespace Common
