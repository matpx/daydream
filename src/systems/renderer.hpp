#pragma once

#include "../nocopy.hpp"
#include "../world.hpp"
#include <memory>

namespace dd {

class Renderer : NoCopy {
    private:
        std::shared_ptr<World> world;

    public:
        Renderer(std::shared_ptr<World> _world) : world(_world) {}

        void update();
};

} // namespace dd
