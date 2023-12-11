#include "sokol_app.h"
#include "sokol_log.h"

#include "log.hpp"
#include "renderer.hpp"
#include <gsl/pointers>

namespace dd {

class App : NoCopy {
public:
  gsl::not_null<std::unique_ptr<Renderer>> renderer;

  App() : renderer(std::make_unique<Renderer>()){};
};

} // namespace dd

static std::unique_ptr<dd::App> app;

void init() { app = std::make_unique<dd::App>(); }

void frame() {}

void cleanup() { app = nullptr; }

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
