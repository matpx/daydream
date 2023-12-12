#include "sokol_app.h"
#include "sokol_log.h"

#include "app.hpp"
#include "log.hpp"
#include "renderer.hpp"

static dd::App *app = nullptr;

void init() { app = new dd::App(); }

void frame() {
  app->renderer->begin_frame();

  app->renderer->end_fram();
}

void cleanup() { delete app; }

void event(const sapp_event *event) {
  if (event->type == SAPP_EVENTTYPE_KEY_DOWN &&
      event->key_code == SAPP_KEYCODE_ESCAPE) {
    sapp_request_quit();
  }
}

sapp_desc sokol_main([[maybe_unused]] int argc, [[maybe_unused]] char *argv[]) {
  DD_LOG_DEBUG("DEBUG MODE!")

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
