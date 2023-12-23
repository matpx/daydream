#pragma once

#include <nvrhi/nvrhi.h>

namespace dd {

struct Vertex {
        std::array<float, 3> position;
};

using Index = uint32_t;

struct MeshData {
        std::vector<Vertex> vertex_data;
        std::vector<Index> index_data;

        nvrhi::BufferHandle vertex_buffer;
        nvrhi::BufferHandle index_buffer;
};

struct MeshSlice {
        uint64_t offset;
        uint32_t element_count;
};

} // namespace dd
