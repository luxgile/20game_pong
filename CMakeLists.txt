cmake_minimum_required(VERSION 3.6)
project(kingdom_lite LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)

include(FetchContent)

FetchContent_Declare(
  raylib
  GIT_REPOSITORY https://github.com/raysan5/raylib 
  GIT_TAG c1ab645ca298a2801097931d1079b10ff7eb9df8
)
FetchContent_MakeAvailable(raylib)

add_executable(${PROJECT_NAME} src/main.cpp src/game.cpp src/game.h)
target_link_libraries(${PROJECT_NAME} raylib)
