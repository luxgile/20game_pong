#pragma once
#include "flecs.h"
#include "raylib.h"
#include "common.h"

namespace paddle {

struct module {
  module(flecs::world &world);
};

struct Paddle {};

struct Score {
  int left = 0;
  int right = 0;
};

void setup_systems(flecs::world &world);

} // namespace Paddle
