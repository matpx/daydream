#include "renderer.hpp"
#include "log.hpp"
#include <nvrhi/d3d11.h>
#include <nvrhi/utils.h>
#include <nvrhi/validation.h>
#include <stdint.h>

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
    // nvrhiDevice = nvrhi::validation::createValidationLayer(nvrhiDevice);
#endif

    std::pair<uint32_t, uint32_t> window_size = window.get_width_height();

    auto textureDesc = nvrhi::TextureDesc()
                           .setDimension(nvrhi::TextureDimension::Texture2D)
                           .setFormat(nvrhi::Format::RGBA8_UNORM)
                           .setWidth(window_size.first)
                           .setHeight(window_size.second)
                           .setIsRenderTarget(true)
                           .setDebugName("Swap Chain Image");

    swapChainTexture = nvrhiDevice->createHandleForNativeTexture(nvrhi::ObjectTypes::D3D11_Resource,
                                                                 window.get_d3d11_backbuffer(), textureDesc);

    auto framebufferDesc = nvrhi::FramebufferDesc().addColorAttachment(swapChainTexture);

    framebuffer = nvrhiDevice->createFramebuffer(framebufferDesc);
}

Renderer::~Renderer() {}

void Renderer::begin_frame() {
    nvrhi::CommandListHandle commandList = nvrhiDevice->createCommandList();

    commandList->open();
    nvrhi::utils::ClearColorAttachment(commandList, framebuffer, 0, nvrhi::Color(1, 0, 0, 1));
    commandList->close();

    nvrhiDevice->executeCommandList(commandList);
}

void Renderer::end_fram() {}

} // namespace dd
