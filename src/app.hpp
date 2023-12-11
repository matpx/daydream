#pragma once

#include "nocopy.hpp"
#include <gsl/pointers>

namespace dd {

class Renderer;

class App : NoCopy {
public:
  gsl::not_null<std::unique_ptr<Renderer>> renderer;

  App();
};

} // namespace dd
