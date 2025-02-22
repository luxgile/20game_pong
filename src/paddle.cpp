
#include "paddle.h"
#include "common.h"
#include <string>

using namespace common;

paddle::module::module(flecs::world &world) {
  world.component<Paddle>();
  world.component<Score>().member<float>("left").member<float>("right");

  world.system<Velocity2D>().with<Player>().each(
      [](Velocity2D& vel) {
        if (IsKeyDown(KEY_W)) {
          vel.value.y -= 200.0f * GetFrameTime();
        }
        if (IsKeyDown(KEY_S)) {
          vel.value.y += 200.0f * GetFrameTime();
        }
      });

  auto phases = world.get<PipelinePhases>();
  world.system<const Score>("Display score").kind(phases->RenderPhase).each(
      [](const Score &score) {
        DrawText(std::to_string(score.left).c_str(), 100, 10, 20, WHITE);
        DrawText(std::to_string(score.right).c_str(), 800 - 100, 10, 20,
                 WHITE);
      }
  );
}
