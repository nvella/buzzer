#include <pebble.h>
#include "main_window.h"

// Supports up to two digits, no negatives
// Returns digits used
// Does not append NULL
int itoa(int i, char* buffer) {
  if(i < 0) return 0; // Negative not supported
  if(i < 10) { // Single digit
    buffer[0] = (char)(48 + i);
    return 1;
  } else {
    buffer[0] = (char)(48 + i / 10);
    buffer[1] = (char)(48 + i % 10);
    return 2;
  }
}

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
