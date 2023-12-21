#pragma once

#include "nocopy.hpp"
#include "window.hpp"
#include <nvrhi/nvrhi.h>

namespace dd {

struct GPUPipeline {
        nvrhi::ShaderHandle vertexShader;
        nvrhi::ShaderHandle pixelShader;
        nvrhi::BindingLayoutHandle bindingLayout;
        nvrhi::BindingSetHandle bindingSet;
        nvrhi::GraphicsPipelineHandle graphicsPipeline;
};

class Renderer final : NoCopy {
    private:
        nvrhi::DeviceHandle nvrhiDevice;
        nvrhi::FramebufferHandle framebuffer;
        nvrhi::TextureHandle color_attachment;
        nvrhi::TextureHandle depth_attachment;
        nvrhi::BufferHandle transform_constant_buffer;

        GPUPipeline unlit_pipeline;

    public:
        Renderer(Window &window);
        ~Renderer();

        void begin_frame();
        void end_fram();
};

} // namespace dd
