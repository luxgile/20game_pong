
#include "paddle.h"
#include "common.h"
#include <string>

using namespace common;

paddle::module::module(flecs::world &world) {
  world.component<Paddle>();
  world.component<Score>().member<float>("left").member<float>("right");
  world.system<Position2D>().with<Player>().each(
      [](flecs::entity paddle, Position2D &pos) {
        if (IsKeyDown(KEY_W)) {
          pos.value.y -= 200.0f * GetFrameTime();
        }
        if (IsKeyDown(KEY_S)) {
          pos.value.y += 200.0f * GetFrameTime();
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
