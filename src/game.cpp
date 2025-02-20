#include "game.h"
#include "common.h"
#include "paddle.h"
#include "raylib.h"

using namespace Common;
using namespace Paddle;

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
  Common::setup_systems(world);
  Paddle::setup_systems(world);
  auto paddle = world.entity("Left paddle")
    .add<CPlayer>()
    .add<CPaddle>()
    .set<CRectangle>({WHITE, 100, 100})
    .set<CPosition>({100, 100});
}
