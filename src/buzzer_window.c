#include <pebble.h>

#include "buzzer.h"
#include "main_window.h"
#include "buzzer_window.h"

int buzzer_window_time;

void buzzer_window_update_time() {
  // Create countdown string
  // mins:seconds 01:23
  int mins = buzzer_window_time / 60;
  int secs = buzzer_window_time % 60;

  static char buffer[] = "00:00";
  // Set minutes
  buffer[0] = (char)(48 + mins / 10);
  buffer[1] = (char)(48 + mins % 10);
  // Set seconds
  buffer[3] = (char)(48 + secs / 10);
  buffer[4] = (char)(48 + secs % 10);

  text_layer_set_text(buzzer_window_text_layer_time, buffer);
}

void buzzer_window_timer_handler(void *context) {
  buzzer_window_time--;

  if(buzzer_window_time < 0) {
    // Buzzer time is under zero, reset it to the minute setting and buzz
    buzzer_window_time = main_window_buzz_time_mins * 60 - 1;
    vibes_double_pulse();
  }

  // Update the time
  buzzer_window_update_time();

  // Reset the timeout
  app_timer_register(1000, buzzer_window_timer_handler, NULL);
}

void buzzer_window_select_click_handler(ClickRecognizerRef recognizer, void *context) {
  // Pause the timer
}

void buzzer_window_click_config_provider(void *context) {
  // Only the select button does something
  window_single_click_subscribe(BUTTON_ID_SELECT, buzzer_window_select_click_handler);
}

void buzzer_window_load(Window *window) {
  Layer *window_layer = window_get_root_layer(window);
  GRect bounds = layer_get_bounds(window_layer);

  // Set buzzer time
  buzzer_window_time = main_window_buzz_time_mins * 60 - 1;

  // Set up time text layer "XX mins"
  buzzer_window_text_layer_time = text_layer_create(GRect(0, bounds.size.h / 2 - 42 / 2 - 10, bounds.size.w, 42));
  buzzer_window_update_time();
  text_layer_set_text_alignment(buzzer_window_text_layer_time, GTextAlignmentCenter);
  text_layer_set_font(buzzer_window_text_layer_time, fonts_get_system_font(FONT_KEY_BITHAM_42_BOLD));
  layer_add_child(window_layer, text_layer_get_layer(buzzer_window_text_layer_time));

  // Set the timer
  app_timer_register(1000, buzzer_window_timer_handler, NULL);
}

void buzzer_window_unload(Window *window) {
  text_layer_destroy(buzzer_window_text_layer_time);
}
