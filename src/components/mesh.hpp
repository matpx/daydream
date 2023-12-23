#pragma once

#include "../mesh.hpp"
#include <gsl/pointers>

namespace dd {

struct MeshComponent {
        gsl::not_null<std::shared_ptr<MeshData>> mesh_data;
        MeshSlice mesh_slice;
};

} // namespace dd
