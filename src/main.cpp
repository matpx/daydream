#include "app.hpp"
#include "log.hpp"

#include "loader.hpp"
#include "renderer.hpp"
#include "world.hpp"

#include <SDL2/SDL.h>

int main([[maybe_unused]] int argc, [[maybe_unused]] char *argv[]) {
    dd::log(dd::LogServerity::DEBUG, "Debug Mode!");

    return 0;
}
