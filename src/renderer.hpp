#pragma once

#include "nocopy.hpp"
#include "window.hpp"
#include <nvrhi/nvrhi.h>

namespace dd {

class Renderer final : NoCopy {
    private:
        nvrhi::DeviceHandle nvrhiDevice;
        nvrhi::FramebufferHandle framebuffer;
        nvrhi::TextureHandle swapChainTexture;

    public:
        Renderer(Window &window);
        ~Renderer();

        void begin_frame();
        void end_fram();
};

} // namespace dd
