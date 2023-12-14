#pragma once

#include "nocopy.hpp"
#include <gsl/pointers>

namespace dd {

class Renderer;
class World;
class Loader;

class App final : NoCopy {
public:
  gsl::not_null<std::unique_ptr<Renderer>> renderer;
  gsl::not_null<std::unique_ptr<Loader>> loader;
  gsl::not_null<std::unique_ptr<World>> world;

  App();
};

extern App *APP;

} // namespace dd
