#include "app.hpp"
#include "loader.hpp"
#include "renderer.hpp"
#include "world.hpp"

namespace dd {

App *APP = nullptr;

App::App()
    : renderer(std::make_unique<Renderer>()),
      loader(std::make_unique<Loader>()), world(std::make_unique<World>()){};

} // namespace dd
