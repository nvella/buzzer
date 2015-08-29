#pragma once

Window *main_window;
TextLayer *main_window_text_layer_1;
TextLayer *main_window_text_layer_time;

void main_window_click_config_provider(void *context);

void main_window_load(Window *window);

void main_window_unload(Window *window);

int main_window_buzz_time_mins;
