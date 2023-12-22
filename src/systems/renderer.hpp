#pragma once

#include "../nocopy.hpp"
#include <memory>

namespace dd {

class World;
class Device;

} // namespace dd

namespace dd::renderer {

void update(Device &device, World &world);

}
