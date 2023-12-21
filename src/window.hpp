#pragma once

#include "nocopy.hpp"
#include <utility>
#include <SDL2/SDL_syswm.h>

class SDL_Window;

namespace dd {

class Window final : NoCopy {
        SDL_Window *sdl_window = nullptr;

    public:
        Window();
        ~Window();

        [[nodiscard]] bool poll();

        [[nodiscard]] std::pair<uint32_t, uint32_t> get_width_height();
        [[nodiscard]] HWND get_hwnd();
};

} // namespace dd
