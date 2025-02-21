#include "ball.h"
#include "common.h"
#include <cstdlib>

using namespace common;

const int WND_WIDTH = 800;
const int WND_HEIGHT = 600;

ball::module::module(flecs::world &world) {
  world.component<Ball>();

  world.system<Position2D, Velocity2D>("Ball collisions")
      .with<Ball>()
      .each([](Position2D &pos, Velocity2D &vel) {
        if (pos.value.x < 0) {
          pos.value.x = 0;
          vel.value.x = abs(vel.value.x);
        }
        if (pos.value.x > WND_WIDTH) {
          pos.value.x = WND_WIDTH;
          vel.value.x = -abs(vel.value.x);
        }
        if (pos.value.y < 0) {
          pos.value.y = 0;
          vel.value.y = abs(vel.value.y);
        }
        if (pos.value.y > WND_HEIGHT) {
          pos.value.y = WND_HEIGHT;
          vel.value.y = -abs(vel.value.y);
        }
      });
}
