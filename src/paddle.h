#pragma once
#include "flecs.h"
#include "flecs/addons/cpp/world.hpp"
#include "raylib.h"
#include "common.h"

namespace paddle {

struct module {
  module(flecs::world &world);
};

struct Paddle {};

void setup_systems(flecs::world &world);

} // namespace Paddle
