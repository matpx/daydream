#define SOKOL_APP_IMPL
#define SOKOL_LOG_IMPL
#define SOKOL_GLCORE33
// #define SOKOL_GLES3
#include "sokol/sokol_app.h"
#include "sokol/sokol_glue.h"
#include "sokol/sokol_log.h"

#include "engine.hpp"

void init() {}

void frame() {}

void cleanup() {}

void event(const sapp_event *event) {
  if (event->type == SAPP_EVENTTYPE_KEY_DOWN &&
      event->key_code == SAPP_KEYCODE_ESCAPE) {
    sapp_request_quit();
  }
}

sapp_desc sokol_main([[maybe_unused]] int argc, [[maybe_unused]] char *argv[]) {
  DD_LOG_DEBUG("DEBUG MODE!");


  return {
      .init_cb = init,
      .frame_cb = frame,
      .cleanup_cb = cleanup,
      .event_cb = event,
      .width = 1200,
      .height = 800,
      .window_title = "daydream",
      .logger =
          {
              .func = slog_func,
          },
  };
}
