#pragma once
#include "flecs.h"
#include "raylib.h"
#include "common.h"

namespace Paddle {

struct CPaddle {};

void setup_systems(flecs::world &world);

} // namespace Paddle
