#include "loader.hpp"
#include "cgltf.h"
#include <gsl/util>
#include <span>
#include <string>
#include <tl/expected.hpp>

namespace dd {

tl::expected<tl::monostate, std::string> parse_prim(const cgltf_primitive &prim) {
    cgltf_attribute pos_attribute = {};

    for (const cgltf_attribute &attribute : std::span<cgltf_attribute>(prim.attributes, prim.attributes_count)) {
        if (attribute.type == cgltf_attribute_type_position) {
            pos_attribute = attribute;
        }

        if (attribute.data->is_sparse == true) {
            return tl::make_unexpected("cgltf prim contains sparse attribute");
        }
    }

    if (pos_attribute.type != cgltf_attribute_type_position) {
        return tl::make_unexpected("cgltf prim contains no position attribute");
    }

    return {};
}

tl::expected<tl::monostate, std::string> load_gltf() {
    const cgltf_options options = {};

    const char *path = "test.glb";

    cgltf_data *data = nullptr;

    auto _ = gsl::finally([&data] { cgltf_free(data); });

    if (cgltf_parse_file(&options, path, &data) != cgltf_result_success) {
        return tl::make_unexpected("gltf parse error");
    }

    if (cgltf_load_buffers(&options, data, path) != cgltf_result_success) {
        return tl::make_unexpected("gltf load buffers error");
    }

    if (cgltf_validate(data) != cgltf_result_success) {
        return tl::make_unexpected("gltf validate error");
    }

    // for(const cgltf_mesh& mesh : std::span<cgltf_mesh>(data->meshes,
    // data->meshes_count)) {

    // }

    return {};
}

} // namespace dd
