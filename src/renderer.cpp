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

    nvrhi::d3d11::DeviceDesc deviceDesc = {
        .messageCallback = static_cast<nvrhi::IMessageCallback *>(&message_callback),
        .context = window.get_d3d11_device_context(),
    };

    nvrhiDevice = nvrhi::d3d11::createDevice(deviceDesc);

#ifndef NDEBUG
    nvrhiDevice = nvrhi::validation::createValidationLayer(nvrhiDevice);
#endif

    std::pair<uint32_t, uint32_t> window_size = window.get_width_height();

    const auto textureDesc = nvrhi::TextureDesc()
                                 .setDimension(nvrhi::TextureDimension::Texture2D)
                                 .setFormat(nvrhi::Format::RGBA8_UNORM)
                                 .setWidth(window_size.first)
                                 .setHeight(window_size.second)
                                 .setIsRenderTarget(true)
                                 .setDebugName("Swap Chain Image");

    color_attachment = nvrhiDevice->createHandleForNativeTexture(nvrhi::ObjectTypes::D3D11_Resource,
                                                                 window.get_d3d11_backbuffer(), textureDesc);

    const auto depth_texture_desc = nvrhi::TextureDesc{
        .width = window_size.first,
        .height = window_size.second,
        .format = nvrhi::Format::D24S8,
        .dimension = nvrhi::TextureDimension::Texture2D,
        .debugName = "Depth Buffer",
        .isRenderTarget = true,
        .isUAV = false,
        .isTypeless = true,
        .clearValue = nvrhi::Color(0),
        .useClearValue = true,
        .initialState = nvrhi::ResourceStates::DepthWrite,
        .keepInitialState = true,
    };

    depth_attachment = nvrhiDevice->createTexture(depth_texture_desc);

    auto framebufferDesc =
        nvrhi::FramebufferDesc().addColorAttachment(color_attachment).setDepthAttachment(depth_attachment);

    framebuffer = nvrhiDevice->createFramebuffer(framebufferDesc);

    {
        auto constantBufferDesc = nvrhi::BufferDesc()
                                      .setByteSize(sizeof(float) * 16) // TODO sizeof(T)
                                      .setIsConstantBuffer(true)
                                      .setIsVolatile(true)
                                      .setMaxVersions(16);

        transform_constant_buffer = nvrhiDevice->createBuffer(constantBufferDesc);
    }

    {
        unlit_pipeline.vertexShader = nvrhiDevice->createShader(nvrhi::ShaderDesc(nvrhi::ShaderType::Vertex),
                                                                g_unlit_main_vs_dxbc, sizeof(g_unlit_main_vs_dxbc));

        nvrhi::VertexAttributeDesc attributes[] = {
            nvrhi::VertexAttributeDesc()
                .setName("POSITION")
                .setFormat(nvrhi::Format::RGB32_FLOAT)
                .setOffset(offsetof(Vertex, position))
                .setElementStride(sizeof(Vertex)),
        };

        nvrhi::InputLayoutHandle inputLayout =
            nvrhiDevice->createInputLayout(attributes, uint32_t(std::size(attributes)), unlit_pipeline.vertexShader);

        unlit_pipeline.pixelShader = nvrhiDevice->createShader(nvrhi::ShaderDesc(nvrhi::ShaderType::Pixel),
                                                               g_unlit_main_ps_dxbc, sizeof(g_unlit_main_ps_dxbc));

        auto layoutDesc = nvrhi::BindingLayoutDesc()
                              .setVisibility(nvrhi::ShaderType::All)
                              .addItem(nvrhi::BindingLayoutItem::VolatileConstantBuffer(0));

        unlit_pipeline.bindingLayout = nvrhiDevice->createBindingLayout(layoutDesc);

        auto bindingSetDesc =
            nvrhi::BindingSetDesc().addItem(nvrhi::BindingSetItem::ConstantBuffer(0, transform_constant_buffer));
        unlit_pipeline.bindingSet = nvrhiDevice->createBindingSet(bindingSetDesc, unlit_pipeline.bindingLayout);

        auto pipelineDesc = nvrhi::GraphicsPipelineDesc()
                                .setInputLayout(inputLayout)
                                .setVertexShader(unlit_pipeline.vertexShader)
                                .setPixelShader(unlit_pipeline.pixelShader)
                                .addBindingLayout(unlit_pipeline.bindingLayout);

        unlit_pipeline.graphicsPipeline = nvrhiDevice->createGraphicsPipeline(pipelineDesc, framebuffer);
    }
}

Renderer::~Renderer() {}

void Renderer::begin_frame() {
    nvrhi::CommandListHandle commandList = nvrhiDevice->createCommandList();

    commandList->open();
    nvrhi::utils::ClearColorAttachment(commandList, framebuffer, 0, nvrhi::Color(0.1f, 0.1f, 0.1f, 1.0f));
    commandList->clearDepthStencilTexture(framebuffer->getDesc().depthAttachment.texture,
                                          framebuffer->getDesc().depthAttachment.subresources, true, 1.0f, true, 0.0f);
    commandList->close();

    nvrhiDevice->executeCommandList(commandList);
}

void Renderer::end_fram() {
    {
        static const std::array<Vertex, 3> g_Vertices = {Vertex{{0.5f, -0.5f, 0.0f}}, Vertex{{-0.5f, -0.5f, 0.0f}},
                                                         Vertex{{0.0f, 0.5f, 0.0f}}};

        auto vertexBufferDesc = nvrhi::BufferDesc()
                                    .setByteSize(sizeof(g_Vertices))
                                    .setIsVertexBuffer(true)
                                    .setInitialState(nvrhi::ResourceStates::VertexBuffer)
                                    .setKeepInitialState(true)
                                    .setDebugName("Vertex Buffer");

        nvrhi::BufferHandle vertexBuffer = nvrhiDevice->createBuffer(vertexBufferDesc);

        nvrhi::CommandListHandle commandList = nvrhiDevice->createCommandList();
        commandList->open();

        commandList->writeBuffer(vertexBuffer, g_Vertices.data(), sizeof(g_Vertices));

        float viewProjectionMatrix[16] = {
            1, 0, 0, 0,

            0, 1, 0, 0,

            0, 0, 1, 0,

            0, 0, 0, 1,
        };
        commandList->writeBuffer(transform_constant_buffer, viewProjectionMatrix, sizeof(viewProjectionMatrix));

        nvrhi::VertexBufferBinding vertex_buffer_binding = {
            .buffer = vertexBuffer,
            .slot = 0,
            .offset = 0,
        };

        auto graphicsState = nvrhi::GraphicsState()
                                 .setPipeline(unlit_pipeline.graphicsPipeline)
                                 .setFramebuffer(framebuffer)
                                 .setViewport(nvrhi::ViewportState().addViewportAndScissorRect(
                                     nvrhi::Viewport(static_cast<float>(framebuffer->getFramebufferInfo().width),
                                                     static_cast<float>(framebuffer->getFramebufferInfo().height))))
                                 .addBindingSet(unlit_pipeline.bindingSet)
                                 .addVertexBuffer(vertex_buffer_binding);
        commandList->setGraphicsState(graphicsState);

        auto drawArguments = nvrhi::DrawArguments().setVertexCount(std::size(g_Vertices));
        commandList->draw(drawArguments);

        commandList->close();
        nvrhiDevice->executeCommandList(commandList);

        nvrhiDevice->runGarbageCollection();
    }
}

} // namespace dd
