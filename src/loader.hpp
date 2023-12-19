#pragma once

#include "components/mesh.hpp"
#include "components/transform.hpp"
#include "nocopy.hpp"
#include <optional>


namespace dd {

struct Prefab {
        struct Node {
                std::optional<MeshComponent> mesh;
                TransformComponent transform;
        };

        std::vector<Node> nodes;
};

class Loader : NoCopy {};

} // namespace dd
