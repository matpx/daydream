#include "app.hpp"
#include "loader.hpp"
#include "renderer.hpp"
#include "window.hpp"
#include "world.hpp"

namespace dd {

App::App()
    : window(std::make_unique<Window>()), renderer(std::make_unique<Renderer>(*window)), loader(std::make_unique<Loader>()),
      world(std::make_unique<World>()){};

void App::run() {
    for (;;) {
        if (window->poll()) {
            return;
        }

        renderer->begin_frame();
        renderer->end_fram();
    }
}

} // namespace dd
