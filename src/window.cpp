#include "window.hpp"

#include <SDL2/SDL.h>
#include <gsl/util>

namespace dd {

Window::Window() {
    SDL_Init(SDL_INIT_EVERYTHING);

    sdl_window = SDL_CreateWindow("game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1200, 800, 0);

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

} // namespace dd
