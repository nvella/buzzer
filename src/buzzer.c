#include <pebble.h>

#include "buzzer.h"
#include "main_window.h"
#include "buzzer_window.h"

// Supports up to two digits, no negatives
// Returns digits used
// Does not append NULL
char* itoa(int i, char* buffer) {
  if(i < 0 || i > 100) return NULL; // Number too high or too low
  if(i < 10) { // Single digit
    buffer[0] = (char)(48 + i);
    return buffer + 1;
  } else {
    buffer[0] = (char)(48 + i / 10);
    buffer[1] = (char)(48 + i % 10);
    return buffer + 2;
  }
}

static void init(void) {
  // Create all the windows
  // main_window
  main_window = window_create();
  window_set_click_config_provider(main_window, main_window_click_config_provider);
  window_set_window_handlers(main_window, (WindowHandlers) {
    .load = main_window_load,
    .unload = main_window_unload,
  });
  // buzzer_window
  buzzer_window = window_create();
  window_set_click_config_provider(buzzer_window, buzzer_window_click_config_provider);
  window_set_window_handlers(buzzer_window, (WindowHandlers) {
    .load = buzzer_window_load,
    .unload = buzzer_window_unload,
  });

  // Push the main window onto the stack to kick it off
  const bool animated = true;
  window_stack_push(main_window, animated);
}

static void deinit(void) {
  // Destroy all the windows
  window_destroy(main_window);
  window_destroy(buzzer_window);
}

int main(void) {
  init();

  APP_LOG(APP_LOG_LEVEL_DEBUG, "Done initializing, pushed window: %p", main_window);

  app_event_loop();
  deinit();
}
