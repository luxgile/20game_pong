#include "game.h"
#include "ai.h"
#include "common.h"
#include "paddle.h"
#include "ball.h"
#include "raylib.h"

using namespace common;

Game::Game() {}

Game::~Game() { CloseWindow(); }

void Game::process_frame(float delta) { world.progress(); }

void Game::init_window(const int screen_width, const int screen_height,
                       const char *title) {
  InitWindow(screen_width, screen_height, title);

  // For this game the camera will be static, I'm not going to work on a fully fledge camera and local positions.
  /* SetWindowState(FLAG_WINDOW_RESIZABLE); */
}

void Game::set_target_fps(const int fps) { SetTargetFPS(fps); }

void Game::start_game() {
  InitAudioDevice();

  world.set<flecs::Rest>({});
  world.import <flecs::stats>();
  world.import <common::module>();
  world.import <paddle::module>();
  world.import<ball::module>();
  world.import<ai::module>();

  world.set<paddle::Score>({.left = 0, .right = 0});

  world.script_run_file("flecs/main.flecs");
}
