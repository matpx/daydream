#include "loader.hpp"
#include "cgltf.h"
#include <gsl/util>
#include <memory>
#include <tl/expected.hpp>

#pragma clang diagnostic ignored "-Wunsafe-buffer-usage"

namespace dd {

static tl::expected<MeshComponent, std::string> parse_prim(gsl::not_null<std::shared_ptr<MeshData>> &mesh_data,
                                                           const cgltf_primitive &prim) {
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

    const uint32_t base_vertex = static_cast<uint32_t>(mesh_data->vertex_data.size());

    for (cgltf_size i_component = 0; i_component < pos_attribute.data->count; i_component++) {
        std::array<float, 3> vertex_pos = {};

        if (!cgltf_accessor_read_float(pos_attribute.data, i_component, vertex_pos.data(), vertex_pos.size())) {
            return tl::make_unexpected("cgltf failed to read position component");
        }

        mesh_data->vertex_data.push_back({
            .position = vertex_pos,
        });
    }

    if (prim.indices->is_sparse) {
        return tl::make_unexpected("cgltf prim contains sparse index accessor");
    }

    MeshComponent mesh_component = {
        .mesh_data = mesh_data,
        .element_offset = static_cast<uint32_t>(mesh_data->index_data.size()),
    };

    for (cgltf_size i_index = 0; i_index < prim.indices->count; i_index++) {
        mesh_data->index_data.push_back(base_vertex +
                                        static_cast<uint32_t>(cgltf_accessor_read_index(prim.indices, i_index)));
    }

    mesh_component.element_count = static_cast<uint32_t>(mesh_data->index_data.size()) - mesh_component.element_offset;

    return mesh_component;
}

static void parse_node(Prefab &prefab, const std::unordered_map<std::uintptr_t, MeshComponent> &mesh_components,
                       const cgltf_node &node) {
    Prefab::Node prefab_node = {};

    if (node.has_translation) {
        prefab_node.transform.translation = glm::vec3(node.translation[0], node.translation[1], node.translation[2]);
    }

    if (node.has_rotation) {
        prefab_node.transform.rotation =
            glm::quat(node.rotation[3], node.rotation[0], node.rotation[1], node.rotation[2]);
    }

    if (node.mesh) {
        const auto mesh_component_iter = mesh_components.find(reinterpret_cast<std::uintptr_t>(node.mesh->primitives));
        if (mesh_component_iter != mesh_components.end()) {
            prefab_node.mesh = mesh_component_iter->second;
        }
    }

    for (const gsl::not_null<const cgltf_node *const> child :
         std::span<cgltf_node *>(node.children, node.children_count)) {
        parse_node(prefab, mesh_components, *child);
    }

    prefab.nodes.push_back(prefab_node);
}

tl::expected<tl::monostate, std::string> load_gltf() {
    const cgltf_options options = {};

    const std::string_view path = "test.glb";

    gsl::owner<cgltf_data *> data = nullptr;

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

    gsl::not_null<std::shared_ptr<MeshData>> mesh_data = std::make_shared<MeshData>();
    std::unordered_map<std::uintptr_t, MeshComponent> mesh_components;

    for (const cgltf_mesh &mesh : std::span<cgltf_mesh>(data->meshes, data->meshes_count)) {
        for (const cgltf_primitive &prim : std::span<cgltf_primitive>(mesh.primitives, mesh.primitives_count)) {
            auto prim_result = parse_prim(mesh_data, prim);
            if (!prim_result) {
                return tl::make_unexpected(prim_result.error());
            }

            mesh_components.emplace(reinterpret_cast<std::uintptr_t>(mesh.primitives), prim_result.value());
        }
    }

    Prefab prefab;

    for (const cgltf_node &node : std::span<cgltf_node>(data->nodes, data->nodes_count)) {
        parse_node(prefab, mesh_components, node);
    }

    return {};
}

} // namespace dd
