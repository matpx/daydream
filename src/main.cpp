#include "app.hpp"
#include "log.hpp"

#include "loader.hpp"
#include "device.hpp"
#include "window.hpp"
#include "world.hpp"
#include "systems/renderer.hpp"
#include "systems/player.hpp"

using namespace dd;

int main([[maybe_unused]] int argc, [[maybe_unused]] char *argv[]) {
    log(LogServerity::DEBUG, "Debug Mode!");

    gsl::not_null<std::unique_ptr<App>> app = std::make_unique<App>();

    app->run();

    return 0;
}
