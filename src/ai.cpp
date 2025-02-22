#include "ai.h"
#include "ball.h"
#include "common.h"
#include "flecs.h"
#include "flecs/addons/cpp/entity.hpp"
#include "paddle.h"
#include "raymath.h"
#include <algorithm>
#include <cstdio>

using namespace common;

namespace ai {
module::module(flecs::world &world) {
  world.component<AI>();

  auto balls = world.query_builder<Position2D>().with<ball::Ball>().build();
  world.system<const Position2D, Velocity2D, const Rect>("AI move paddle")
      .with<paddle::Paddle>()
      .with<AI>()
      .each([balls](const Position2D &paddle_pos, Velocity2D &paddle_vel, const Rect &paddle_rect) {
        auto closest_ball = flecs::entity();
        float closest_dist = 99999.0f;

        // Find closest ball
        balls.each([&](flecs::entity ball_e, Position2D &ball_pos) {
          float dist = Vector2Distance(ball_pos.value, paddle_pos.value);
          if (dist < closest_dist) {
            closest_dist = dist;
            closest_ball = ball_e;
          }
        });

        if (closest_ball) {
          auto ball_pos = closest_ball.get<Position2D>();
          auto diff = ball_pos->value.y - (paddle_pos.value.y + paddle_rect.height / 2);
          auto movement = diff > 0.0f ? 1.0f : -1.0f;
          auto speed = 500.0f;
          paddle_vel.value.y += movement * speed * GetFrameTime();
        }
      });
}
} // namespace ai
