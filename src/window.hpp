#pragma once

#include "nocopy.hpp"

struct SDL_Window;

namespace dd {

class Window final : NoCopy {
        SDL_Window *sdl_window = nullptr;

    public:
        Window();
        ~Window();

        [[nodiscard]] bool poll();
};

} // namespace dd
