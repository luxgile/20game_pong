#include "common.h"
#include "flecs.h"
#include "raylib.h"
#include <cmath>

namespace common {
common::module::module(flecs::world &world) {
  // TODO: Move raylib module somewhere else
  world.component<Player>();
  world.component<Position2D>().member<float>("x").member<float>("y");
  world.component<Velocity2D>().member<float>("x").member<float>("y");
  world.component<Damping>().member<float>("value");
  world.component<Circle>().member<float>("radius");
  world.component<Circle>().member<float>("radius");
  world.component<Rect>().member<float>("width").member<float>("height");
  world.component<BaseColor>()
      .member<unsigned char>("r")
      .member<unsigned char>("g")
      .member<unsigned char>("b")
      .member<unsigned char>("a");
  world.component<PipelinePhases>().member<flecs::entity>("RenderPhase");

  // Setup systems
  world.system("Start render").kind(flecs::PreStore).each([]() {
    BeginDrawing();
    ClearBackground(BLACK);
    DrawFPS(10, 10);
  });

  world.system("Stop render").kind(flecs::OnStore).each([]() { EndDrawing(); });

  
  auto RenderPhase =
      world.entity().add(flecs::Phase).depends_on(flecs::PreStore);
  world.set<PipelinePhases>({.RenderPhase = RenderPhase});

  world
      .system<const Position2D, const Rect, const BaseColor>(
          "Draw rectangles")
      .kind(RenderPhase)
      .each([](const Position2D &pos, const Rect &rect,
               const BaseColor &color) {
        DrawRectangle(pos.value.x, pos.value.y, rect.width, rect.height,
                      color.value);
      });

  world.system<const Position2D, const Circle, const BaseColor>("Draw Circles")
      .kind(RenderPhase)
      .each([](const Position2D &pos, const Circle &circle,
               const BaseColor &color) {
        DrawCircle(pos.value.x, pos.value.y, circle.radius, color.value);
      });

  world.system<const Velocity2D, Position2D>("Apply velocity to position")
      .each([](const Velocity2D &velocity, Position2D &position) {
        position.value += velocity.value * GetFrameTime();
      });

  world.system<Velocity2D, const Damping>("Apply damping to velocity")
      .each([](Velocity2D &velocity, const Damping &damping) {
        velocity.value *= std::pow(1.0f - damping.value, GetFrameTime());  
  });
}
} // namespace common
