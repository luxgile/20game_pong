#include "common.h"
#include "flecs/addons/cpp/c_types.hpp"
#include "flecs/addons/cpp/mixins/pipeline/decl.hpp"
#include <cstdio>

namespace Common {

void setup_systems(flecs::world &world) {
  world.system("Start render").kind(flecs::PreStore).each([]() {
    BeginDrawing();
    ClearBackground(BLACK);
    DrawFPS(10, 10);
  });

  world.system("Stop render").kind(flecs::OnStore).each([]() {
    EndDrawing();
  });


  auto RenderPhase = world.entity().add(flecs::Phase).depends_on(flecs::PreStore);
  world.system<const CPosition, const CRectangle>("Draw rectangles").kind(RenderPhase).each(
      [](const CPosition &pos, const CRectangle &rect) {
        DrawRectangle(pos.value.x, pos.value.y, rect.width, rect.height,
                      rect.color);
      });
}
} // namespace Common
