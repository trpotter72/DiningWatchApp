#pragma once
#include <pebble.h>

#include "phone_comms.h"


uint16_t menu_get_num_sections_callback(MenuLayer *main_layer, void *data);
uint16_t menu_get_num_rows_callback(MenuLayer *main_layer, uint16_t section_index, void *data) ;
int16_t menu_get_header_height_callback(MenuLayer *main_layer, uint16_t section_index, void *data);

void menu_draw_header_callback(GContext* ctx, const Layer *cell_layer, uint16_t section_index, void *data);

void menu_draw_row_callback(GContext* ctx, const Layer *cell_layer, MenuIndex *cell_index, void *data) ;

void menu_select_callback(MenuLayer *main_layer, MenuIndex *cell_index, void *data) ;
void setup_menu1_layer(Window *window) ;
void menu_window_load(Window* window);

void menu_window_create(int val);

void menu_window_destroy(Window* window);
Window* menu_window_get_window();