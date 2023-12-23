#include "renderer.hpp"
#include "../components/mesh.hpp"
#include "../components/transform.hpp"
#include "../device.hpp"
#include "../world.hpp"
#include <memory>

namespace dd::renderer {

void update(Device &device, World &world) {
    static bool first_run = true;

    if (first_run) {
        std::shared_ptr<MeshData> triangle_data = std::make_shared<MeshData>(MeshData{
            .vertex_data = {Vertex{{0.5f, -0.5f, 0.0f}}, Vertex{{-0.5f, -0.5f, 0.0f}}, Vertex{{0.0f, 0.5f, 0.0f}}},
            .index_data = {0, 1, 2},
        });

        MeshComponent triangle_mesh = {.mesh_data = std::move(triangle_data),
                                       .mesh_slice = {
                                           .offset = 0,
                                           .element_count = 3,
                                       }};

        entt::entity triangle_entity = world.create();
        world.emplace<TransformComponent>(triangle_entity, TransformComponent{});
        world.emplace<MeshComponent>(triangle_entity, triangle_mesh);

        first_run = false;
    }

    nvrhi::CommandListHandle command_list = device.nvrhi_device->createCommandList();
    command_list->open();

    for (const auto [entity, transform, mesh] : world.view<TransformComponent, MeshComponent>().each()) {
        if (mesh.mesh_data->vertex_buffer.Get() == nullptr || mesh.mesh_data->index_buffer.Get() == nullptr) {

            const size_t vertex_buffer_size = mesh.mesh_data->vertex_data.size() * sizeof(Vertex);
            const auto vertex_buffer_desc = nvrhi::BufferDesc()
                                                .setByteSize(vertex_buffer_size)
                                                .setInitialState(nvrhi::ResourceStates::VertexBuffer)
                                                .setKeepInitialState(true)
                                                .setIsVertexBuffer(true)
                                                .setDebugName("Vertex Buffer");

            mesh.mesh_data->vertex_buffer = device.nvrhi_device->createBuffer(vertex_buffer_desc);
            command_list->writeBuffer(mesh.mesh_data->vertex_buffer, mesh.mesh_data->vertex_data.data(),
                                      vertex_buffer_size);

            const size_t index_buffer_size = mesh.mesh_data->index_data.size() * sizeof(Index);
            const auto index_buffer_desc = nvrhi::BufferDesc()
                                               .setByteSize(index_buffer_size)
                                               .setInitialState(nvrhi::ResourceStates::IndexBuffer)
                                               .setKeepInitialState(true)
                                               .setIsIndexBuffer(true)
                                               .setDebugName("Index Buffer");

            mesh.mesh_data->index_buffer = device.nvrhi_device->createBuffer(index_buffer_desc);
            command_list->writeBuffer(mesh.mesh_data->index_buffer, mesh.mesh_data->index_data.data(),
                                      index_buffer_size);
        }

        float mvp[16] = {
            1, 0, 0, 0,

            0, 1, 0, 0,

            0, 0, 1, 0,

            0, 0, 0, 1,
        };
        command_list->writeBuffer(device.transform_constant_buffer, mvp, sizeof(mvp));

        const auto vertex_buffer_binding =
            nvrhi::VertexBufferBinding().setBuffer(mesh.mesh_data->vertex_buffer).setOffset(mesh.mesh_slice.offset);

        const auto graphicsState = nvrhi::GraphicsState()
                                       .setPipeline(device.unlit_pipeline.graphics_pipeline)
                                       .setFramebuffer(device.framebuffer)
                                       .setViewport(nvrhi::ViewportState().addViewportAndScissorRect(nvrhi::Viewport(
                                           static_cast<float>(device.framebuffer->getFramebufferInfo().width),
                                           static_cast<float>(device.framebuffer->getFramebufferInfo().height))))
                                       .addBindingSet(device.unlit_pipeline.binding_set)
                                       .addVertexBuffer(vertex_buffer_binding);
        command_list->setGraphicsState(graphicsState);

        const auto draw_arguments = nvrhi::DrawArguments().setVertexCount(mesh.mesh_slice.element_count);
        command_list->draw(draw_arguments);
    }

    command_list->close();
    device.nvrhi_device->executeCommandList(command_list);
}

} // namespace dd::renderer
