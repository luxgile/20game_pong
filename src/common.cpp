#include "common.h"
#include "flecs/addons/cpp/c_types.hpp"
#include "flecs/addons/cpp/mixins/pipeline/decl.hpp"
#include <cstdio>

namespace common {
common::module::module(flecs::world &world) {
  world.component<Player>();
  world.component<Position2D>();
  world.component<Rectangle>();
  world.component<BaseColor>();

  // Setup systems
  world.system("Start render").kind(flecs::PreStore).each([]() {
    BeginDrawing();
    ClearBackground(BLACK);
    DrawFPS(10, 10);
  });

  world.system("Stop render").kind(flecs::OnStore).each([]() { EndDrawing(); });

  auto RenderPhase =
      world.entity().add(flecs::Phase).depends_on(flecs::PreStore);

  world.system<const Position2D, const Rectangle, const BaseColor>("Draw rectangles")
      .kind(RenderPhase)
      .each([](const Position2D &pos, const Rectangle &rect, const BaseColor &color) {
        DrawRectangle(pos.value.x, pos.value.y, rect.width, rect.height,
                      color.value);
      });
}
} // namespace common
