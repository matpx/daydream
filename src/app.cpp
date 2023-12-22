#include "app.hpp"
#include "device.hpp"
#include "loader.hpp"
#include "systems/player.hpp"
#include "systems/renderer.hpp"
#include "window.hpp"
#include "world.hpp"

namespace dd {

App::App()
    : window(std::make_unique<Window>()), device(std::make_unique<Device>(*window)), loader(std::make_unique<Loader>()),
      world(std::make_shared<World>()), renderer(std::make_unique<Renderer>(world)),
      player(std::make_unique<Player>()){};

void App::run() {
    for (;;) {
        if (window->poll()) {
            return;
        }

        renderer->update();

        device->begin_frame();
        device->end_fram();
    }
}

} // namespace dd
