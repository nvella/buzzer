#include <pebble.h>
#include "main_window.h"

static void init(void) {
  // Create all the windows
  main_window = window_create();
  window_set_click_config_provider(main_window, main_window_click_config_provider);
  window_set_window_handlers(main_window, (WindowHandlers) {
    .load = main_window_load,
    .unload = main_window_unload,
  });

  // Push the main window onto the stack to kick it off
  const bool animated = true;
  window_stack_push(main_window, animated);
}

static void deinit(void) {
  // Destroy all the windows
  window_destroy(main_window);
}

int main(void) {
  init();

  APP_LOG(APP_LOG_LEVEL_DEBUG, "Done initializing, pushed window: %p", main_window);

  app_event_loop();
  deinit();
}
