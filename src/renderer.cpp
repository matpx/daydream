#include "renderer.hpp"
#include "components/mesh.hpp"
#include "log.hpp"
#include <nvrhi/d3d11.h>
#include <nvrhi/utils.h>
#include <nvrhi/validation.h>
#include <stdint.h>

#include "shader/unlit_main_ps.dxbc.h"
#include "shader/unlit_main_vs.dxbc.h"

namespace dd {

class MessageCallback : public nvrhi::IMessageCallback {
        virtual void message([[maybe_unused]] nvrhi::MessageSeverity severity, const char *messageText) override {
            log(LogServerity::INFO, "NHRHI: {}", messageText);
        }
};

Renderer::Renderer(Window &window) {
    [[clang::no_destroy]] static MessageCallback message_callback;

    nvrhi::d3d11::DeviceDesc device_desc = {
        .messageCallback = static_cast<nvrhi::IMessageCallback *>(&message_callback),
        .context = window.get_d3d11_device_context(),
    };

    nvrhi_device = nvrhi::d3d11::createDevice(device_desc);

#ifndef NDEBUG
    nvrhi_device = nvrhi::validation::createValidationLayer(nvrhi_device);
#endif

    std::pair<uint32_t, uint32_t> window_size = window.get_width_height();

    const auto color_texture_desc = nvrhi::TextureDesc()
                                        .setDimension(nvrhi::TextureDimension::Texture2D)
                                        .setFormat(nvrhi::Format::RGBA8_UNORM)
                                        .setWidth(window_size.first)
                                        .setHeight(window_size.second)
                                        .setIsRenderTarget(true)
                                        .setDebugName("Swap Chain Image");

    color_attachment_texture = nvrhi_device->createHandleForNativeTexture(
        nvrhi::ObjectTypes::D3D11_Resource, window.get_d3d11_backbuffer(), color_texture_desc);

    const auto depth_texture_desc = nvrhi::TextureDesc()
                                        .setWidth(window_size.first)
                                        .setHeight(window_size.second)
                                        .setFormat(nvrhi::Format::D24S8)
                                        .setDimension(nvrhi::TextureDimension::Texture2D)
                                        .setDebugName("Depth Buffer")
                                        .setIsRenderTarget(true)
                                        .setIsUAV(false)
                                        .setIsTypeless(true)
                                        .setClearValue(nvrhi::Color(0))
                                        .setUseClearValue(true)
                                        .setInitialState(nvrhi::ResourceStates::DepthWrite)
                                        .setKeepInitialState(true);

    depth_attachment_texture = nvrhi_device->createTexture(depth_texture_desc);

    auto framebuffer_desc = nvrhi::FramebufferDesc()
                                .addColorAttachment(color_attachment_texture)
                                .setDepthAttachment(depth_attachment_texture);

    framebuffer = nvrhi_device->createFramebuffer(framebuffer_desc);

    {
        auto transform_constant_buffer_desc = nvrhi::BufferDesc()
                                                  .setByteSize(sizeof(float) * 16) // TODO sizeof(T)
                                                  .setIsConstantBuffer(true)
                                                  .setIsVolatile(true)
                                                  .setMaxVersions(16);

        transform_constant_buffer = nvrhi_device->createBuffer(transform_constant_buffer_desc);
    }

    {
        unlit_pipeline.vertex_shader = nvrhi_device->createShader(nvrhi::ShaderDesc(nvrhi::ShaderType::Vertex),
                                                                  g_unlit_main_vs_dxbc, sizeof(g_unlit_main_vs_dxbc));

        nvrhi::VertexAttributeDesc attributes[] = {
            nvrhi::VertexAttributeDesc()
                .setName("POSITION")
                .setFormat(nvrhi::Format::RGB32_FLOAT)
                .setOffset(offsetof(Vertex, position))
                .setElementStride(sizeof(Vertex)),
        };

        nvrhi::InputLayoutHandle input_layout =
            nvrhi_device->createInputLayout(attributes, uint32_t(std::size(attributes)), unlit_pipeline.vertex_shader);

        unlit_pipeline.pixel_shader = nvrhi_device->createShader(nvrhi::ShaderDesc(nvrhi::ShaderType::Pixel),
                                                                 g_unlit_main_ps_dxbc, sizeof(g_unlit_main_ps_dxbc));

        auto layout_desc = nvrhi::BindingLayoutDesc()
                               .setVisibility(nvrhi::ShaderType::All)
                               .addItem(nvrhi::BindingLayoutItem::VolatileConstantBuffer(0));

        unlit_pipeline.binding_layout = nvrhi_device->createBindingLayout(layout_desc);

        auto binding_set_desc =
            nvrhi::BindingSetDesc().addItem(nvrhi::BindingSetItem::ConstantBuffer(0, transform_constant_buffer));
        unlit_pipeline.binding_set = nvrhi_device->createBindingSet(binding_set_desc, unlit_pipeline.binding_layout);

        auto pipeline_desc = nvrhi::GraphicsPipelineDesc()
                                 .setInputLayout(input_layout)
                                 .setVertexShader(unlit_pipeline.vertex_shader)
                                 .setPixelShader(unlit_pipeline.pixel_shader)
                                 .addBindingLayout(unlit_pipeline.binding_layout);

        unlit_pipeline.graphics_pipeline = nvrhi_device->createGraphicsPipeline(pipeline_desc, framebuffer);
    }
}

Renderer::~Renderer() {}

void Renderer::begin_frame() {
    nvrhi::CommandListHandle command_list = nvrhi_device->createCommandList();

    command_list->open();
    nvrhi::utils::ClearColorAttachment(command_list, framebuffer, 0, nvrhi::Color(0.1f, 0.1f, 0.1f, 1.0f));
    command_list->clearDepthStencilTexture(framebuffer->getDesc().depthAttachment.texture,
                                           framebuffer->getDesc().depthAttachment.subresources, true, 1.0f, true, 0.0f);
    command_list->close();

    nvrhi_device->executeCommandList(command_list);
}

void Renderer::end_fram() {
    {
        static const std::array<Vertex, 3> g_Vertices = {Vertex{{0.5f, -0.5f, 0.0f}}, Vertex{{-0.5f, -0.5f, 0.0f}},
                                                         Vertex{{0.0f, 0.5f, 0.0f}}};

        auto vertex_buffer_desc = nvrhi::BufferDesc()
                                      .setByteSize(sizeof(g_Vertices))
                                      .setIsVertexBuffer(true)
                                      .setInitialState(nvrhi::ResourceStates::VertexBuffer)
                                      .setKeepInitialState(true)
                                      .setDebugName("Vertex Buffer");

        nvrhi::BufferHandle vertex_buffer = nvrhi_device->createBuffer(vertex_buffer_desc);

        nvrhi::CommandListHandle command_list = nvrhi_device->createCommandList();
        command_list->open();

        command_list->writeBuffer(vertex_buffer, g_Vertices.data(), sizeof(g_Vertices));

        float mvp[16] = {
            1, 0, 0, 0,

            0, 1, 0, 0,

            0, 0, 1, 0,

            0, 0, 0, 1,
        };
        command_list->writeBuffer(transform_constant_buffer, mvp, sizeof(mvp));

        nvrhi::VertexBufferBinding vertex_buffer_binding = {
            .buffer = vertex_buffer,
            .slot = 0,
            .offset = 0,
        };

        auto graphicsState = nvrhi::GraphicsState()
                                 .setPipeline(unlit_pipeline.graphics_pipeline)
                                 .setFramebuffer(framebuffer)
                                 .setViewport(nvrhi::ViewportState().addViewportAndScissorRect(
                                     nvrhi::Viewport(static_cast<float>(framebuffer->getFramebufferInfo().width),
                                                     static_cast<float>(framebuffer->getFramebufferInfo().height))))
                                 .addBindingSet(unlit_pipeline.binding_set)
                                 .addVertexBuffer(vertex_buffer_binding);
        command_list->setGraphicsState(graphicsState);

        auto draw_arguments = nvrhi::DrawArguments().setVertexCount(std::size(g_Vertices));
        command_list->draw(draw_arguments);

        command_list->close();
        nvrhi_device->executeCommandList(command_list);

        nvrhi_device->runGarbageCollection();
    }
}

} // namespace dd
