#include <pebble.h>

#include "buzzer.h"
#include "main_window.h"
#include "buzzer_window.h"

int buzzer_window_time;
bool buzzer_window_paused;
int buzzer_window_buzzes;
AppTimer* buzzer_window_timer;

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

  static char buzz_buffer[] = "Buzzes: 000000000"; // Can only make the buffer so long
  char* end_of_buzzes = itoa(buzzer_window_buzzes, buzz_buffer + 8);
  *end_of_buzzes = 0;
  text_layer_set_text(buzzer_window_text_layer_buzzes, buzz_buffer);
}

void buzzer_window_timer_handler(void *context) {
  if(buzzer_window_paused) return; // Don't do anything if the timer is paused

  buzzer_window_time--;

  if(buzzer_window_time < 0) {
    // Buzzer time is under zero, reset it to the minute setting and buzz
    buzzer_window_time = main_window_buzz_time_mins * 60 - 1;
    buzzer_window_buzzes++;
    vibes_double_pulse();
  }

  // Update the time
  buzzer_window_update_time();

  // Reset the timeout
  buzzer_window_timer = app_timer_register(1000, buzzer_window_timer_handler, NULL);
}

void buzzer_window_select_click_handler(ClickRecognizerRef recognizer, void *context) {
  // (Un)pause the timer
  buzzer_window_paused = !buzzer_window_paused;

  if(buzzer_window_paused) {
    // Set paused text layer
    text_layer_set_text(buzzer_window_text_layer_paused, "Paused");
  } else {
    // Blank paused layer
    text_layer_set_text(buzzer_window_text_layer_paused, "");
    // Reset timer
    buzzer_window_timer = app_timer_register(1000, buzzer_window_timer_handler, NULL);
  }

  vibes_short_pulse();
}

void buzzer_window_click_config_provider(void *context) {
  // Only the select button does something
  window_single_click_subscribe(BUTTON_ID_SELECT, buzzer_window_select_click_handler);
}

void buzzer_window_load(Window *window) {
  Layer *window_layer = window_get_root_layer(window);
  GRect bounds = layer_get_bounds(window_layer);

  // Set buzzer time and paused status
  buzzer_window_time = main_window_buzz_time_mins * 60 - 1;
  buzzer_window_paused = false;
  buzzer_window_buzzes = 0;

  // Set up time text layer "XX mins"
  buzzer_window_text_layer_time = text_layer_create(GRect(0, bounds.size.h / 2 - 42 / 2 - 10, bounds.size.w, 42));
  text_layer_set_text_alignment(buzzer_window_text_layer_time, GTextAlignmentCenter);
  text_layer_set_font(buzzer_window_text_layer_time, fonts_get_system_font(FONT_KEY_BITHAM_42_BOLD));
  layer_add_child(window_layer, text_layer_get_layer(buzzer_window_text_layer_time));

  // Set up paused text layer
  buzzer_window_text_layer_paused = text_layer_create(GRect(0, bounds.size.h / 4 - 20 / 2 - 11, bounds.size.w, 22));
  text_layer_set_text_alignment(buzzer_window_text_layer_paused, GTextAlignmentCenter);
  text_layer_set_font(buzzer_window_text_layer_paused, fonts_get_system_font(FONT_KEY_GOTHIC_18));
  layer_add_child(window_layer, text_layer_get_layer(buzzer_window_text_layer_paused));

  // Set up buzzes text layer
  buzzer_window_text_layer_buzzes = text_layer_create(GRect(0, bounds.size.h / 4 * 3 - 20 / 2 - 2, bounds.size.w, 22));
  text_layer_set_text_alignment(buzzer_window_text_layer_buzzes, GTextAlignmentCenter);
  text_layer_set_font(buzzer_window_text_layer_buzzes, fonts_get_system_font(FONT_KEY_GOTHIC_18));
  layer_add_child(window_layer, text_layer_get_layer(buzzer_window_text_layer_buzzes));

  // Update the time (and other stuff)
  buzzer_window_update_time();

  // Set the timer
  buzzer_window_timer = app_timer_register(1000, buzzer_window_timer_handler, NULL);
}

void buzzer_window_unload(Window *window) {
  text_layer_destroy(buzzer_window_text_layer_time);
  text_layer_destroy(buzzer_window_text_layer_paused);
  text_layer_destroy(buzzer_window_text_layer_buzzes);

  buzzer_window_paused = true; // "pause" the timer, causing it to stop at next tick
  app_timer_cancel(buzzer_window_timer); // cancel it anyway
}
