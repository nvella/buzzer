#pragma once

Window *buzzer_window;
TextLayer *buzzer_window_text_layer_time;
TextLayer *buzzer_window_text_layer_paused;

void buzzer_window_click_config_provider(void *context);

void buzzer_window_load(Window *window);

void buzzer_window_unload(Window *window);
