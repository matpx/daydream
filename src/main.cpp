#define SOKOL_APP_IMPL
#define SOKOL_LOG_IMPL
#define SOKOL_GLCORE33
#include <sokol_app.h>
#include <sokol_glue.h>
#include <sokol_log.h>

void init() {}

void frame() {}

void cleanup() {}

void event(const sapp_event *event) {
  if(event->type == SAPP_EVENTTYPE_KEY_DOWN && event->key_code == SAPP_KEYCODE_ESCAPE) {
    sapp_request_quit();
  }  
}

sapp_desc sokol_main(int argc, char *argv[]) {
  return {
      .init_cb = init,
      .frame_cb = frame,
      .cleanup_cb = cleanup,
      .event_cb = event,
      .width = 1200,
      .height = 800,
      .window_title = "Triangle (sokol-app)",
      .logger =
          {
              .func = slog_func,
          },
  };
}
