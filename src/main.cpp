#include "app.hpp"
#include "device.hpp"
#include "loader.hpp"
#include "window.hpp"
#include "world.hpp"
#include <spdlog/spdlog.h>

using namespace dd;

int main([[maybe_unused]] int argc, [[maybe_unused]] char *argv[]) {
#ifndef NDEBUG
    spdlog::set_level(spdlog::level::debug);
#endif

    spdlog::debug("Debug Mode!");

    gsl::not_null<std::unique_ptr<App>> app = std::make_unique<App>();

    app->run();

    return 0;
}
