#include "window.hpp"

#include <SDL2/SDL.h>
#include <SDL2/SDL_syswm.h>
#include <d3d11.h>
#include <gsl/util>

namespace dd {

Window::Window() {
    SDL_Init(SDL_INIT_EVERYTHING);

    sdl_window = SDL_CreateWindow("game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1200, 800, 0);

    Ensures(sdl_window);

    SDL_SysWMinfo wmInfo;
    SDL_VERSION(&wmInfo.version)
    SDL_GetWindowWMInfo(sdl_window, &wmInfo);
    HWND hwnd = wmInfo.info.win.window;

    DXGI_SWAP_CHAIN_DESC swap_chain_desc;

    ZeroMemory(&swap_chain_desc, sizeof(DXGI_SWAP_CHAIN_DESC));

    swap_chain_desc.BufferCount = 1;
    swap_chain_desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    swap_chain_desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    swap_chain_desc.OutputWindow = hwnd;
    swap_chain_desc.SampleDesc.Count = 4;
    swap_chain_desc.Windowed = TRUE;

    D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, 0, nullptr, 0, D3D11_SDK_VERSION, &swap_chain_desc,
                                  &d3d11_swapchain, &d3d11_devive, nullptr, &d3d11_device_context);
}

Window::~Window() {
    d3d11_swapchain->Release();
    d3d11_devive->Release();
    d3d11_device_context->Release();

    SDL_DestroyWindow(sdl_window);
    SDL_Quit();
}

bool Window::poll() {
    bool want_quit = false;

    SDL_Event window_event;
    while (SDL_PollEvent(&window_event)) {
        if (window_event.type == SDL_QUIT ||
            (window_event.type == SDL_KEYDOWN && window_event.key.keysym.sym == SDLK_ESCAPE)) {
            want_quit = true;
        }
    }

    return want_quit;
}

} // namespace dd
