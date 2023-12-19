#pragma once

#include <array>
#include <gsl/pointers>
#include <memory>
#include <stdint.h>
#include <vector>

namespace dd {

struct Vertex {
        std::array<float, 3> pos;
};

using index_t = uint32_t;

struct MeshData {
        std::vector<Vertex> vertex_data;
        std::vector<index_t> index_data;

        // buffer
};

struct MeshComponent {
        gsl::not_null<std::shared_ptr<MeshData>> mesh_data;
        uint32_t element_offset;
        uint32_t element_count;
};

} // namespace dd
