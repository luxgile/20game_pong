
#include "paddle.h"
#include "common.h"

using namespace common;

paddle::module::module(flecs::world &world) {
  world.system<Position2D>().with<Player>()
    .each([](flecs::entity paddle, Position2D &pos) {
        if (IsKeyDown(KEY_W)) {
          pos.value.y -= 200.0f * GetFrameTime();
        }
        if (IsKeyDown(KEY_S)) {
          pos.value.y += 200.0f * GetFrameTime();
        }
      });
}

