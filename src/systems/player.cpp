#include "player.hpp"
#include <spdlog/spdlog.h>

namespace dd::player {

void update(World &world, Loader &loader) {
    static bool first_run = true;

    if (first_run) {
        first_run = false;

        tl::expected<PrefabHandle, std::string> test_gltf = loader.load_gltf("assets/glb/test.glb");

        if (test_gltf) {
            loader.instantiate(world, test_gltf.value());
        } else {
            spdlog::error(test_gltf.error());
        }
    }
}

} // namespace dd::player
