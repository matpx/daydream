#include "sokol_app.h"
#include "sokol_log.h"

#include "app.hpp"
#include "log.hpp"

#include "loader.hpp"
#include "renderer.hpp"
#include "world.hpp"

namespace dd {

static void init() {
    log(LogServerity::DEBUG, "Debug Mode!");
    APP = new App();
}

static void frame() {
    APP->renderer->begin_frame();

    APP->renderer->end_fram();
}

static void cleanup() { delete APP; }

static void event(const sapp_event *event) {
    if (event->type == SAPP_EVENTTYPE_KEY_DOWN &&
        event->key_code == SAPP_KEYCODE_ESCAPE) {
        sapp_request_quit();
    }
}

} // namespace dd

sapp_desc sokol_main([[maybe_unused]] int argc, [[maybe_unused]] char *argv[]) {
    return {
        .init_cb = dd::init,
        .frame_cb = dd::frame,
        .cleanup_cb = dd::cleanup,
        .event_cb = dd::event,
        .width = 1200,
        .height = 800,
        .window_title = "daydream",
        .logger =
            {
                .func = slog_func,
            },
    };
}
