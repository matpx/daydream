#pragma once

#include "nocopy.hpp"
#include <utility>

class SDL_Window;
class IDXGISwapChain;
class ID3D11Device;
class ID3D11DeviceContext;
class ID3D11Texture2D;

namespace dd {

class Window final : NoCopy {
        SDL_Window *sdl_window = nullptr;

        ID3D11Device *d3d11_device = nullptr;
        ID3D11DeviceContext *d3d11_device_context = nullptr;
        IDXGISwapChain *d3d11_swapchain = nullptr;
        ID3D11Texture2D *d3d11_backbuffer = nullptr;

    public:
        Window();
        ~Window();

        [[nodiscard]] bool poll();
        void present();

        [[nodiscard]] constexpr ID3D11DeviceContext *get_d3d11_device_context() { return d3d11_device_context; }
        [[nodiscard]] constexpr ID3D11Texture2D *get_d3d11_backbuffer() { return d3d11_backbuffer; }
        [[nodiscard]] std::pair<uint32_t, uint32_t> get_width_height();
};

} // namespace dd
