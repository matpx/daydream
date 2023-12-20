#include "renderer.hpp"
#include "log.hpp"
#include <nvrhi/d3d11.h>
#include <nvrhi/validation.h>

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

    nvrhi::DeviceHandle nvrhiDevice = nvrhi::d3d11::createDevice(deviceDesc);

#ifndef NDEBUG
    nvrhiDevice = nvrhi::validation::createValidationLayer(nvrhiDevice);
#endif
}

Renderer::~Renderer() {}

void Renderer::begin_frame() {}

void Renderer::end_fram() {}

} // namespace dd
