#pragma once
#include "flecs.h"

// Game
class Game {
private:
  flecs::world world;

public:
  Game();
  ~Game();

  void init_window(const int screen_width, const int screen_height,
                   const char *title);
  void set_target_fps(const int fps);

  void start_game();

  void process_frame(float delta);
};
