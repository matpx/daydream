#include "loader.hpp"
#include "cgltf.h"
#include <gsl/util>
#include <gsl/pointers>
#include <span>
#include <string>
#include <tl/expected.hpp>
#include "components/transform.hpp"

namespace dd {

static tl::expected<tl::monostate, std::string> parse_prim(const cgltf_primitive &prim) {
    cgltf_attribute pos_attribute = {};

    for (const cgltf_attribute &attribute : std::span<cgltf_attribute>(prim.attributes, prim.attributes_count)) {
        if (attribute.type == cgltf_attribute_type_position) {
            pos_attribute = attribute;
        }

        if (attribute.data->is_sparse) {
            return tl::make_unexpected("cgltf prim contains sparse accessor");
        }
    }

    if (pos_attribute.type != cgltf_attribute_type_position) {
        return tl::make_unexpected("cgltf prim contains no position attribute");
    }

    for(cgltf_size i_component = 0; i_component < pos_attribute.data->count; i_component++) {
        std::array<float, 3> vertex_pos = {};

        if(!cgltf_accessor_read_float(pos_attribute.data, i_component, vertex_pos.data(), vertex_pos.size())) {
            return tl::make_unexpected("cgltf failed to read position component");
        }
    }

    if(prim.indices->is_sparse) {
        return tl::make_unexpected("cgltf prim contains sparse index accessor");
    }

    // for(cgltf_size i_index = 0; i_index < prim.indices->count; i_index++) {
    //     const uint32_t index = static_cast<uint32_t>(cgltf_accessor_read_index(prim.indices, i_index));
    // }

    return {};
}

// static void parse_node(const cgltf_node& node) {
//     for(gsl::not_null<const cgltf_node* const> child : std::span<cgltf_node*>(node.children, node.children_count)) {
//         parse_node(*child);
//     } 
// }

tl::expected<tl::monostate, std::string> load_gltf() {
    const cgltf_options options = {};

    const std::string_view path = "test.glb";

    gsl::owner<cgltf_data*> data = nullptr;

    auto _ = gsl::finally([&data] { cgltf_free(data); });

    if (cgltf_parse_file(&options, path.data(), &data) != cgltf_result_success) {
        return tl::make_unexpected("gltf parse error");
    }

    if (cgltf_load_buffers(&options, data, path.data()) != cgltf_result_success) {
        return tl::make_unexpected("gltf load buffers error");
    }

    if (cgltf_validate(data) != cgltf_result_success) {
        return tl::make_unexpected("gltf validate error");
    }

    for(const cgltf_mesh& mesh : std::span<cgltf_mesh>(data->meshes, data->meshes_count)) {
        for(const cgltf_primitive& prim : std::span<cgltf_primitive>(mesh.primitives, mesh.primitives_count)) {
            auto prim_result = parse_prim(prim);
            if(!prim_result) {
                return prim_result;
            }
        }
    }

    return {};
}

} // namespace dd
