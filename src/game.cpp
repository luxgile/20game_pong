#include "game.h"
#include "raylib.h"

void Game::process_frame(float delta) {}

void Game::render_frame(float delta) {
  BeginDrawing();

  ClearBackground(RAYWHITE);

  DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);

  EndDrawing();
}
