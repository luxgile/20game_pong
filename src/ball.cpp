#include "ball.h"
#include "common.h"
#include "paddle.h"
#include <cstdlib>

using namespace common;

const int WND_WIDTH = 800;
const int WND_HEIGHT = 600;

ball::module::module(flecs::world &world) {
  world.component<Ball>().member<int>("bounces");

  world
      .system<paddle::Score, Position2D, Velocity2D, const Circle>(
          "Ball collisions")
      .term_at(0)
      .singleton()
      .with<Ball>()
      .each([](paddle::Score &score, Position2D &pos, Velocity2D &vel,
               const Circle &circle) {
        if (pos.value.x < 0 + circle.radius) {
          pos.value.x = 0 + circle.radius;
          vel.value.x = abs(vel.value.x);
          
          // Point for right paddle
          score.right += 1;
        }
        if (pos.value.x > WND_WIDTH - circle.radius) {
          pos.value.x = WND_WIDTH - circle.radius;
          vel.value.x = -abs(vel.value.x);

          // Point for left paddle
          score.left += 1;
        }
        if (pos.value.y < 0 + circle.radius) {
          pos.value.y = 0 + circle.radius;
          vel.value.y = abs(vel.value.y);
        }
        if (pos.value.y > WND_HEIGHT - circle.radius) {
          pos.value.y = WND_HEIGHT - circle.radius;
          vel.value.y = -abs(vel.value.y);
        }
      });
}
