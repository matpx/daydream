#include "app.hpp"
#include "loader.hpp"
#include "renderer.hpp"
#include "window.hpp"
#include "world.hpp"

namespace dd {

App::App()
    : window(std::make_unique<Window>()), renderer(std::make_unique<Renderer>()), loader(std::make_unique<Loader>()),
      world(std::make_unique<World>()){};

void App::run() {
    for (;;) {
        if (window->poll()) {
            return;
        }
    }
}

} // namespace dd
