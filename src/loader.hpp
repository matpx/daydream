#pragma once

#include "components/mesh.hpp"
#include "components/transform.hpp"
#include "nocopy.hpp"
#include "world.hpp"
#include <memory>
#include <optional>
#include <tl/expected.hpp>


namespace dd {

struct Prefab {
        struct Node {
                std::optional<MeshComponent> mesh;
                TransformComponent transform;
        };

        std::vector<Node> nodes;
};

using PrefabHandle = std::shared_ptr<Prefab>;

class Loader : NoCopy {
    public:
        tl::expected<PrefabHandle, std::string> load_gltf(const std::string_view path);

        void instantiate(World &world, const PrefabHandle prefab);
};

} // namespace dd
