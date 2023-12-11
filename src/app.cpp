#include "app.hpp"
#include "renderer.hpp"

namespace dd {

App::App() : renderer(std::make_unique<Renderer>()){};

}
