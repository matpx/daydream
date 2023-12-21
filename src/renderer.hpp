#pragma once

#include "nocopy.hpp"
#include "window.hpp"
#include <nvrhi/nvrhi.h>

namespace dd {

struct GPUPipeline {
        nvrhi::ShaderHandle vertex_shader;
        nvrhi::ShaderHandle pixel_shader;
        nvrhi::BindingLayoutHandle binding_layout;
        nvrhi::BindingSetHandle binding_set;
        nvrhi::GraphicsPipelineHandle graphics_pipeline;
};

class Renderer final : NoCopy {
    private:
        nvrhi::DeviceHandle nvrhi_device;
        nvrhi::FramebufferHandle framebuffer;
        nvrhi::TextureHandle color_attachment_texture;
        nvrhi::TextureHandle depth_attachment_texture;
        nvrhi::BufferHandle transform_constant_buffer;

        GPUPipeline unlit_pipeline;

    public:
        Renderer(Window &window);
        ~Renderer();

        void begin_frame();
        void end_fram();
};

} // namespace dd
