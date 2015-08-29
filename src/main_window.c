#include <pebble.h>

#include "buzzer.h"
#include "main_window.h"
#include "buzzer_window.h"

void main_window_update_time() {
  /**** <- This thing here 'static' => important */
  static char buffer[] = "00 mins";
  char* mins_ptr = itoa(main_window_buzz_time_mins, buffer);
  if(main_window_buzz_time_mins == 1) strcpy(mins_ptr, " min"); else strcpy(mins_ptr, " mins");
  text_layer_set_text(main_window_text_layer_time, buffer);
}

void main_window_select_click_handler(ClickRecognizerRef recognizer, void *context) {
  // Start the timer
  // Push the buzzer window onto the stack
  window_stack_push(buzzer_window, true);
}

void main_window_up_click_handler(ClickRecognizerRef recognizer, void *context) {
  if(main_window_buzz_time_mins < 99)
    main_window_buzz_time_mins++;
  else
    main_window_buzz_time_mins = 1;

  main_window_update_time();
}

void main_window_down_click_handler(ClickRecognizerRef recognizer, void *context) {
  if(main_window_buzz_time_mins > 1)
    main_window_buzz_time_mins--;
  else
    main_window_buzz_time_mins = 99;

  main_window_update_time();
}

void main_window_click_config_provider(void *context) {
  window_single_click_subscribe(BUTTON_ID_SELECT, main_window_select_click_handler);
  window_single_click_subscribe(BUTTON_ID_UP, main_window_up_click_handler);
  window_single_click_subscribe(BUTTON_ID_DOWN, main_window_down_click_handler);
}

void main_window_load(Window *window) {
  main_window_buzz_time_mins = 1;

  Layer *window_layer = window_get_root_layer(window);
  GRect bounds = layer_get_bounds(window_layer);

  // Set up 'info' text layer "Buzz me in:"
  main_window_text_layer_1 = text_layer_create(GRect(0, 39, bounds.size.w, 26));
  text_layer_set_text(main_window_text_layer_1, "Buzz me in");
  text_layer_set_font(main_window_text_layer_1, fonts_get_system_font(FONT_KEY_GOTHIC_24));
  text_layer_set_text_alignment(main_window_text_layer_1, GTextAlignmentCenter);
  layer_add_child(window_layer, text_layer_get_layer(main_window_text_layer_1));

  // Set up time text layer "XX mins"
  main_window_text_layer_time = text_layer_create(GRect(0, 66, bounds.size.w, 50));
  main_window_update_time();
  text_layer_set_text_alignment(main_window_text_layer_time, GTextAlignmentCenter);
  text_layer_set_font(main_window_text_layer_time, fonts_get_system_font(FONT_KEY_BITHAM_30_BLACK));

  layer_add_child(window_layer, text_layer_get_layer(main_window_text_layer_time));
}

void main_window_unload(Window *window) {
  text_layer_destroy(main_window_text_layer_1);
  text_layer_destroy(main_window_text_layer_time);
}
