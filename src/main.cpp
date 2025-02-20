#include "raylib.h"
#include "game.h"

int main(int argc, char *argv[]) {
  const int screen_width = 800;
  const int screen_height = 450;

  InitWindow(screen_width, screen_height, "raylib [core] example - basic window");
  SetTargetFPS(60);

  Game game; 

  while (!WindowShouldClose()) 
  {
    // Update
    game.process_frame(GetFrameTime());

    // Draw
    game.render_frame(GetFrameTime());
    BeginDrawing();

    ClearBackground(RAYWHITE);

    DrawText("Congrats! You created your first window!", 190, 200, 20,
             LIGHTGRAY);

    EndDrawing();
  }

  CloseWindow(); 
  return 0;
}
