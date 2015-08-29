#include <pebble.h>
#include "main_window.h"

void main_window_select_click_handler(ClickRecognizerRef recognizer, void *context) {
  text_layer_set_text(text_layer, "Select");
}

void main_window_up_click_handler(ClickRecognizerRef recognizer, void *context) {
  text_layer_set_text(text_layer, "Up");
}

void main_window_down_click_handler(ClickRecognizerRef recognizer, void *context) {
  text_layer_set_text(text_layer, "Down");
}

void main_window_click_config_provider(void *context) {
  window_single_click_subscribe(BUTTON_ID_SELECT, main_window_select_click_handler);
  window_single_click_subscribe(BUTTON_ID_UP, main_window_up_click_handler);
  window_single_click_subscribe(BUTTON_ID_DOWN, main_window_down_click_handler);
}

void main_window_load(Window *window) {
  Layer *window_layer = window_get_root_layer(window);
  GRect bounds = layer_get_bounds(window_layer);

  text_layer = text_layer_create((GRect) { .origin = { 0, 72 }, .size = { bounds.size.w, 20 } });
  text_layer_set_text(text_layer, "Press a button");
  text_layer_set_text_alignment(text_layer, GTextAlignmentCenter);
  layer_add_child(window_layer, text_layer_get_layer(text_layer));
}

void main_window_unload(Window *window) {
  text_layer_destroy(text_layer);
}
