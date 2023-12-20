#pragma once

#include "nocopy.hpp"
#include "window.hpp"

namespace dd {

class Renderer final : NoCopy {
    public:
        Renderer(Window& window);
        ~Renderer();

        void begin_frame();
        void end_fram();
};

} // namespace dd
