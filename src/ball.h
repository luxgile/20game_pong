#pragma once
#include "flecs.h"

namespace ball {
  struct module {
    module(flecs::world &world);
  };

  struct Ball {
    int bounces = 0;
  };
}
