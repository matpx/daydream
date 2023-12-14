#include "renderer.hpp"
#include <sokol_app.h>
#include <sokol_gfx.h>
#include <sokol_glue.h>
#include <sokol_log.h>

namespace dd {

Renderer::Renderer() {
    sg_setup(sg_desc{
        .logger = {.func = slog_func},
        .context = sapp_sgcontext(),
    });
}

Renderer::~Renderer() { sg_shutdown(); }

void Renderer::begin_frame() {
    const int w = sapp_width();
    const int h = sapp_height();

    sg_pass_action pass_action = {};
    sg_begin_default_pass(&pass_action, w, h);
}

void Renderer::end_fram() {
    sg_end_pass();
    sg_commit();
}

} // namespace dd
