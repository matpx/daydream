#pragma once

#include "nocopy.hpp"

namespace dd {

class Renderer : NoCopy {
public:
  Renderer();
  ~Renderer();

  void begin_frame();
  void end_fram();
};

} // namespace dd
