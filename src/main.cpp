#include "raylib.h"
#include "game.h"

int main(int argc, char *argv[]) {
  Game game; 
  game.init_window(800, 600, "Pong");
  game.set_target_fps(60);

  game.start_game();

  while (!WindowShouldClose()) 
  {
    // Update
    game.process_frame(GetFrameTime());
  }

  return 0;
}
