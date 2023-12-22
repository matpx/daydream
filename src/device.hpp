#pragma once

#include "nocopy.hpp"
#include "window.hpp"
#include <nvrhi/nvrhi.h>

class IDXGISwapChain;
class ID3D11Device;
class ID3D11DeviceContext;
class ID3D11Texture2D;

namespace dd {

struct GPUPipeline {
        nvrhi::ShaderHandle vertex_shader;
        nvrhi::ShaderHandle pixel_shader;
        nvrhi::BindingLayoutHandle binding_layout;
        nvrhi::BindingSetHandle binding_set;
        nvrhi::GraphicsPipelineHandle graphics_pipeline;
};

class Device final : NoCopy {
    private:
        ID3D11Device *d3d11_device = nullptr;
        ID3D11DeviceContext *d3d11_device_context = nullptr;
        IDXGISwapChain *d3d11_swapchain = nullptr;
        ID3D11Texture2D *d3d11_backbuffer = nullptr;

        nvrhi::DeviceHandle nvrhi_device;
        nvrhi::FramebufferHandle framebuffer;
        nvrhi::TextureHandle color_attachment_texture;
        nvrhi::TextureHandle depth_attachment_texture;
        nvrhi::BufferHandle transform_constant_buffer;

        GPUPipeline unlit_pipeline;

        void init_d3d11_device(HWND hwnd, std::pair<uint32_t, uint32_t> window_size);

    public:
        Device(Window &window);
        ~Device();

        void begin_frame();
        void end_fram();
};

} // namespace dd
