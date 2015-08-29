#pragma once

Window *main_window;
TextLayer *text_layer;

void main_window_select_click_handler(ClickRecognizerRef recognizer, void *context);

void main_window_up_click_handler(ClickRecognizerRef recognizer, void *context);

void main_window_down_click_handler(ClickRecognizerRef recognizer, void *context);

void main_window_click_config_provider(void *context);

void main_window_load(Window *window);

void main_window_unload(Window *window);
