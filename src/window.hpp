#pragma once

#include "nocopy.hpp"

class SDL_Window;
class IDXGISwapChain;
class ID3D11Device;
class ID3D11DeviceContext;

namespace dd {

class Window final : NoCopy {
        SDL_Window *sdl_window = nullptr;

        IDXGISwapChain *d3d11_swapchain = nullptr;
        ID3D11Device *d3d11_devive = nullptr;
        ID3D11DeviceContext *d3d11_device_context = nullptr;

    public:
        Window();
        ~Window();

        [[nodiscard]] bool poll();

        [[nodiscard]] constexpr ID3D11DeviceContext *get_d3d11_device_context() { return d3d11_device_context; }
};

} // namespace dd
