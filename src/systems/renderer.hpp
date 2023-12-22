#pragma once

#include "../nocopy.hpp"
#include <memory>

namespace dd {

class World;
class Device;

class Renderer : NoCopy {
    public:
        void update(Device &device, World &world);
};

} // namespace dd
