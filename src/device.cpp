#include "device.hpp"
#include "components/mesh.hpp"
#include "fatal.hpp"
#include "util.hpp"
#include <nvrhi/d3d11.h>
#include <nvrhi/utils.h>
#include <nvrhi/validation.h>
#include <spdlog/spdlog.h>

#include "shader/unlit_main_ps.dxbc.h"
#include "shader/unlit_main_vs.dxbc.h"

namespace dd {

void Device::init_d3d11_device(HWND hwnd, const std::pair<uint32_t, uint32_t> window_size) {
    DXGI_SWAP_CHAIN_DESC swap_chain_desc;

    ZeroMemory(&swap_chain_desc, sizeof(DXGI_SWAP_CHAIN_DESC));

    swap_chain_desc.BufferCount = 1;
    swap_chain_desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    swap_chain_desc.BufferDesc.Width = window_size.first;
    swap_chain_desc.BufferDesc.Height = window_size.second;
    swap_chain_desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    swap_chain_desc.OutputWindow = hwnd;
    swap_chain_desc.SampleDesc.Count = 1;
    swap_chain_desc.Windowed = TRUE;

    HRESULT result = D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, 0, nullptr, 0,
                                                   D3D11_SDK_VERSION, &swap_chain_desc, &d3d11_swapchain, &d3d11_device,
                                                   nullptr, &d3d11_device_context);
    ensure_or_fatal(!FAILED(result), "D3D11CreateDeviceAndSwapChain() failed");

    NOWARN("-Wlanguage-extension-token", {
        result =
            d3d11_swapchain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<LPVOID *>(&d3d11_backbuffer));
    })

    ensure_or_fatal(!FAILED(result), "d3d11_swapchain->GetBuffer() failed");

    class MessageCallback : public nvrhi::IMessageCallback {
        public:
            virtual void message([[maybe_unused]] nvrhi::MessageSeverity severity, const char *messageText) override {
                switch (severity) {
                case nvrhi::MessageSeverity::Info:
                    spdlog::info("NHRHI: {}", messageText);
                    break;
                case nvrhi::MessageSeverity::Warning:
                    spdlog::warn("NHRHI: {}", messageText);
                    break;
                case nvrhi::MessageSeverity::Error:
                case nvrhi::MessageSeverity::Fatal:
                    spdlog::error("NHRHI: {}", messageText);
                    break;
                }
            }
    };

    [[clang::no_destroy]] static MessageCallback message_callback;

    nvrhi::d3d11::DeviceDesc device_desc = {
        .messageCallback = static_cast<nvrhi::IMessageCallback *>(&message_callback),
        .context = d3d11_device_context,
    };

    nvrhi_device = nvrhi::d3d11::createDevice(device_desc);

#ifndef NDEBUG
    nvrhi_device = nvrhi::validation::createValidationLayer(nvrhi_device);
#endif
}

Device::Device(Window &window) {
    const std::pair<uint32_t, uint32_t> window_size = window.get_width_height();

    init_d3d11_device(window.get_hwnd(), window_size);

    {
        const auto color_texture_desc = nvrhi::TextureDesc()
                                            .setDimension(nvrhi::TextureDimension::Texture2D)
                                            .setFormat(nvrhi::Format::RGBA8_UNORM)
                                            .setWidth(window_size.first)
                                            .setHeight(window_size.second)
                                            .setIsRenderTarget(true)
                                            .setDebugName("Swap Chain Image");

        color_attachment_texture = nvrhi_device->createHandleForNativeTexture(nvrhi::ObjectTypes::D3D11_Resource,
                                                                              d3d11_backbuffer, color_texture_desc);

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

        const auto framebuffer_desc = nvrhi::FramebufferDesc()
                                          .addColorAttachment(color_attachment_texture)
                                          .setDepthAttachment(depth_attachment_texture);

        framebuffer = nvrhi_device->createFramebuffer(framebuffer_desc);
    }

    {
        const auto transform_constant_buffer_desc = nvrhi::BufferDesc()
                                                        .setByteSize(sizeof(float) * 16) // TODO sizeof(T)
                                                        .setIsConstantBuffer(true)
                                                        .setIsVolatile(true)
                                                        .setMaxVersions(16);

        transform_constant_buffer = nvrhi_device->createBuffer(transform_constant_buffer_desc);
    }

    {
        unlit_pipeline.vertex_shader = nvrhi_device->createShader(nvrhi::ShaderDesc(nvrhi::ShaderType::Vertex),
                                                                  g_unlit_main_vs_dxbc, sizeof(g_unlit_main_vs_dxbc));

        const nvrhi::VertexAttributeDesc attributes[] = {
            nvrhi::VertexAttributeDesc()
                .setName("POSITION")
                .setFormat(nvrhi::Format::RGB32_FLOAT)
                .setOffset(offsetof(Vertex, position))
                .setElementStride(sizeof(Vertex)),
        };

        const nvrhi::InputLayoutHandle input_layout =
            nvrhi_device->createInputLayout(attributes, uint32_t(std::size(attributes)), unlit_pipeline.vertex_shader);

        unlit_pipeline.pixel_shader = nvrhi_device->createShader(nvrhi::ShaderDesc(nvrhi::ShaderType::Pixel),
                                                                 g_unlit_main_ps_dxbc, sizeof(g_unlit_main_ps_dxbc));

        const auto layout_desc = nvrhi::BindingLayoutDesc()
                                     .setVisibility(nvrhi::ShaderType::All)
                                     .addItem(nvrhi::BindingLayoutItem::VolatileConstantBuffer(0));

        unlit_pipeline.binding_layout = nvrhi_device->createBindingLayout(layout_desc);

        const auto binding_set_desc =
            nvrhi::BindingSetDesc().addItem(nvrhi::BindingSetItem::ConstantBuffer(0, transform_constant_buffer));
        unlit_pipeline.binding_set = nvrhi_device->createBindingSet(binding_set_desc, unlit_pipeline.binding_layout);

        const auto pipeline_desc = nvrhi::GraphicsPipelineDesc()
                                       .setInputLayout(input_layout)
                                       .setVertexShader(unlit_pipeline.vertex_shader)
                                       .setPixelShader(unlit_pipeline.pixel_shader)
                                       .addBindingLayout(unlit_pipeline.binding_layout);

        unlit_pipeline.graphics_pipeline = nvrhi_device->createGraphicsPipeline(pipeline_desc, framebuffer);
    }
}

Device::~Device() {
    d3d11_backbuffer->Release();
    d3d11_swapchain->Release();
    d3d11_device->Release();
    d3d11_device_context->Release();
}

void Device::begin_frame() {
    nvrhi::CommandListHandle command_list = nvrhi_device->createCommandList();

    command_list->open();
    nvrhi::utils::ClearColorAttachment(command_list, framebuffer, 0, nvrhi::Color(0.1f, 0.1f, 0.1f, 1.0f));
    nvrhi::utils::ClearDepthStencilAttachment(command_list, framebuffer, 1.0f, 0.0f);
    command_list->close();

    nvrhi_device->executeCommandList(command_list);
}

void Device::end_fram() {
    d3d11_swapchain->Present(0, 0);

    nvrhi_device->runGarbageCollection();
}

} // namespace dd
