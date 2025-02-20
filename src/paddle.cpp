
#include "paddle.h"

using namespace Common;

void Paddle::setup_systems(flecs::world &world) {
  world.system<CPosition>().with<CPlayer>()
    .each([](flecs::entity paddle, CPosition &pos) {
        if (IsKeyDown(KEY_W)) {
          pos.value.y -= 200.0f * GetFrameTime();
        }
        if (IsKeyDown(KEY_S)) {
          pos.value.y += 200.0f * GetFrameTime();
        }
      });
}
