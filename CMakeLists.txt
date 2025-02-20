cmake_minimum_required(VERSION 3.6)
project(pong_cpp LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)

include(FetchContent)

FetchContent_Declare(
  raylib
  GIT_REPOSITORY https://github.com/raysan5/raylib 
  GIT_TAG c1ab645ca298a2801097931d1079b10ff7eb9df8
)
FetchContent_MakeAvailable(raylib)

FetchContent_Declare(
  flecs
  GIT_REPOSITORY https://github.com/SanderMertens/flecs
  GIT_TAG 8a1e9abe412eda7cd7f2a7440dac7499ce42cdca
)
FetchContent_MakeAvailable(flecs)

add_executable(${PROJECT_NAME}
    src/common.cpp
    src/game.cpp
    src/main.cpp
    src/paddle.cpp
)
target_include_directories(${PROJECT_NAME} PUBLIC src)
target_link_libraries(${PROJECT_NAME} raylib flecs::flecs_static)
