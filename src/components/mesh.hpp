#pragma once

#include <array>
#include <gsl/pointers>
#include <memory>
#include <nvrhi/nvrhi.h>
#include <stdint.h>
#include <vector>

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

struct MeshComponent {
        gsl::not_null<std::shared_ptr<MeshData>> mesh_data;

        nvrhi::VertexBufferBinding vertex_buffer_binding;
        uint32_t element_count;
};

} // namespace dd
