
#include "paddle.h"
#include "common.h"
#include <string>

using namespace common;

const float PLAYER_SPEED = 500.0f;

paddle::module::module(flecs::world &world) {
  world.component<Paddle>();
  world.component<Score>().member<float>("left").member<float>("right");

  world.system<Velocity2D>().with<Player>().each(
      [](Velocity2D& vel) {
        if (IsKeyDown(KEY_W)) {
          vel.value.y -= PLAYER_SPEED * GetFrameTime();
        }
        if (IsKeyDown(KEY_S)) {
          vel.value.y += PLAYER_SPEED * GetFrameTime();
        }
      });

  world.system<Position2D, const Rect>("Clamp paddles").with<Paddle>().each(
      [](Position2D &pos, const Rect &rect) {
        if (pos.value.y < 0.0f) {
          pos.value.y = 0.0f;
        }
        if (pos.value.y + rect.height > 600.0f) {
          pos.value.y = 600.0f - rect.height ;
        }
      }
  );

  auto phases = world.get<PipelinePhases>();
  world.system<const Score>("Display score").kind(phases->RenderPhase).each(
      [](const Score &score) {
        DrawText(std::to_string(score.left).c_str(), 350, 290, 20, WHITE);
        DrawText(std::to_string(score.right).c_str(), 440, 290, 20,
                 WHITE);
      }
  );
}
