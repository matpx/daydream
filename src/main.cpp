#include "sokol_app.h"
#include "sokol_log.h"

#include "app.hpp"
#include "log.hpp"
#include "renderer.hpp"

namespace dd {

static App *app = nullptr;

void init() {
  log(LogServerity::DEBUG, "Debug Mode!");
  app = new App();
}

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
