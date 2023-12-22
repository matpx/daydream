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
      world(std::make_unique<World>()){};

void App::run() {
    for (;;) {
        if (window->poll()) {
            return;
        }

        device->begin_frame();
        renderer::update(*device, *world);
        device->end_fram();
    }
}

} // namespace dd
