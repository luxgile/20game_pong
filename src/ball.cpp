#include "ball.h"
#include "common.h"
#include "paddle.h"
#include "raylib.h"
#include <cstdlib>

using namespace common;

const int WND_WIDTH = 800;
const int WND_HEIGHT = 600;

void reset_ball(Position2D &pos) {
  pos.value.x = WND_WIDTH / 2;
  pos.value.y = WND_HEIGHT / 2;
}

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
          reset_ball(pos);
          score.right += 1;
          vel.value = {-250.0, static_cast<float>(GetRandomValue(-100, 100))};
        }
        if (pos.value.x > WND_WIDTH - circle.radius) {
          reset_ball(pos);
          score.left += 1;
          vel.value = {250.0, static_cast<float>(GetRandomValue(-100, 100))};
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

  auto balls =
      world.query_builder<Velocity2D, Position2D, const Circle>().with<Ball>().build();

  world.system<Position2D, common::Rect, const Velocity2D>("Collide ball with paddles")
      .with<paddle::Paddle>()
      .each([balls](Position2D &paddle_pos, common::Rect &paddle_rect, const Velocity2D &paddle_vel) {
        auto rect = Rectangle {.x = paddle_pos.value.x,
                               .y = paddle_pos.value.y,
                               .width = paddle_rect.width,
                               .height = paddle_rect.height};

        balls.each([&](Velocity2D &ball_vel, Position2D &ball_pos, const Circle &ball) {
          if (CheckCollisionCircleRec(ball_pos.value, ball.radius, rect)) {
              ball_vel.value.x *= -1.2f;
              ball_vel.value.y += paddle_vel.value.y;
          }
        });
      });
}
