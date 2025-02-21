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
  world.import<common::module>();
  world.import<paddle::module>();
  auto paddle = world.entity("Left paddle")
    .add<Player>()
    .add<paddle::Paddle>()
    .set<common::Rectangle>({100, 100})
    .set<common::BaseColor>({GREEN})
    .set<Position2D>({100, 100});
}
