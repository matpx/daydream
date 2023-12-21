#include "window.hpp"

#include <SDL2/SDL.h>
#include <gsl/util>

namespace dd {

Window::Window() {
    SDL_Init(SDL_INIT_EVERYTHING);

    const int w = 1200, h = 800;

    sdl_window = SDL_CreateWindow("game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, w, h, 0);

    Ensures(sdl_window);
}

Window::~Window() {
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

std::pair<uint32_t, uint32_t> Window::get_width_height() {
    int w, h;
    SDL_GetWindowSize(sdl_window, &w, &h);

    return {w, h};
}

HWND Window::get_hwnd() {
    SDL_SysWMinfo wmInfo;
    SDL_VERSION(&wmInfo.version)
    SDL_GetWindowWMInfo(sdl_window, &wmInfo);
    return  wmInfo.info.win.window;
}

} // namespace dd
