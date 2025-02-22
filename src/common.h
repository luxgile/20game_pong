#pragma once
#include "flecs.h"
#include "raylib.h"
#include "raymath.h"

namespace common {

struct module {
  module(flecs::world &world);
};

struct PipelinePhases {
  flecs::entity RenderPhase;
};

/// Tag to reference the player.
struct Player {};

struct Position2D {
  Vector2 value;
};

struct Velocity2D {
  Vector2 value;
};

struct Damping {
  float value;
};

struct Circle {
  float radius;
};

struct Rect {
  float width;
  float height;
};

struct BaseColor {
  Color value;
};
}; // namespace Common


