#include "game.h"
#include "common.h"
#include "paddle.h"
#include "raylib.h"

using namespace common;

Game::Game() { }

Game::~Game() { CloseWindow(); }

void Game::process_frame(float delta) {
  world.progress();
}

void Game::init_window(const int screen_width, const int screen_height,
                       const char *title) {
  InitWindow(screen_width, screen_height, title);
}

void Game::set_target_fps(const int fps) {
  SetTargetFPS(fps);
}

void Game::start_game() {
  world.set<flecs::Rest>({});
  world.import<flecs::stats>();
  world.import<common::module>();
  world.import<paddle::module>();
  world.script_run_file("flecs/paddles.flecs");
}
