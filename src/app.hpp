#pragma once

#include "nocopy.hpp"
#include <gsl/pointers>

namespace dd {

class Window;
class Renderer;
class World;
class Loader;

class App final : NoCopy {
    public:
        gsl::not_null<std::unique_ptr<Window>> window;
        gsl::not_null<std::unique_ptr<Renderer>> renderer;
        gsl::not_null<std::unique_ptr<Loader>> loader;
        gsl::not_null<std::unique_ptr<World>> world;

        App();
        void run();
};

} // namespace dd
