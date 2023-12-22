#include "renderer.hpp"
#include "../components/mesh.hpp"
#include "../components/transform.hpp"
#include "../device.hpp"
#include "../world.hpp"

namespace dd {

void Renderer::update(Device &device, World &) {
    // for (const auto [entity, transform, mesh] : world.view<TransformComponent, MeshComponent>().each()) {
        static const std::array<Vertex, 3> g_Vertices = {Vertex{{0.5f, -0.5f, 0.0f}}, Vertex{{-0.5f, -0.5f, 0.0f}},
                                                         Vertex{{0.0f, 0.5f, 0.0f}}};

        auto vertex_buffer_desc = nvrhi::BufferDesc()
                                      .setByteSize(sizeof(g_Vertices))
                                      .setIsVertexBuffer(true)
                                      .setInitialState(nvrhi::ResourceStates::VertexBuffer)
                                      .setKeepInitialState(true)
                                      .setDebugName("Vertex Buffer");

        nvrhi::BufferHandle vertex_buffer = device.nvrhi_device->createBuffer(vertex_buffer_desc);

        nvrhi::CommandListHandle command_list = device.nvrhi_device->createCommandList();
        command_list->open();

        command_list->writeBuffer(vertex_buffer, g_Vertices.data(), sizeof(g_Vertices));

        float mvp[16] = {
            1, 0, 0, 0,

            0, 1, 0, 0,

            0, 0, 1, 0,

            0, 0, 0, 1,
        };
        command_list->writeBuffer(device.transform_constant_buffer, mvp, sizeof(mvp));

        nvrhi::VertexBufferBinding vertex_buffer_binding = {
            .buffer = vertex_buffer,
            .slot = 0,
            .offset = 0,
        };

        auto graphicsState = nvrhi::GraphicsState()
                                 .setPipeline(device.unlit_pipeline.graphics_pipeline)
                                 .setFramebuffer(device.framebuffer)
                                 .setViewport(nvrhi::ViewportState().addViewportAndScissorRect(nvrhi::Viewport(
                                     static_cast<float>(device.framebuffer->getFramebufferInfo().width),
                                     static_cast<float>(device.framebuffer->getFramebufferInfo().height))))
                                 .addBindingSet(device.unlit_pipeline.binding_set)
                                 .addVertexBuffer(vertex_buffer_binding);
        command_list->setGraphicsState(graphicsState);

        auto draw_arguments = nvrhi::DrawArguments().setVertexCount(std::size(g_Vertices));
        command_list->draw(draw_arguments);

        command_list->close();
        device.nvrhi_device->executeCommandList(command_list);
    // }
}

} // namespace dd
