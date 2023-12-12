#pragma once

#include "nocopy.hpp"
#include "world.hpp"
#include <gsl/pointers>

namespace dd {

class Renderer;

class App final : NoCopy {
public:
  gsl::not_null<std::unique_ptr<Renderer>> renderer;

  std::unique_ptr<World> world;

  App();
};

} // namespace dd
