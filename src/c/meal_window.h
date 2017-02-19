#ifndef MEAL_MENU_H
#define MEAL_MENU_H
#pragma once
#include "phone_comms.h"


#include <pebble.h>
#include "meal_window.h"

Window* mainWindow;
MenuLayer* mainMenuLayer;

uint16_t main_get_num_sections_callback(MenuLayer *main_layer, void *data);
uint16_t main_get_num_rows_callback(MenuLayer *main_layer, uint16_t section_index, void *data);

int16_t main_get_header_height_callback(MenuLayer *main_layer, uint16_t section_index, void *data) ;

void main_draw_header_callback(GContext* ctx, const Layer *cell_layer, uint16_t section_index, void *data);

void main_draw_row_callback(GContext* ctx, const Layer *cell_layer, MenuIndex *cell_index, void *data);

void main_select_callback(MenuLayer *main_layer, MenuIndex *cell_index, void *data);

void setup_main_layer(Window *window) ;
void main_window_load(Window* window);
void main_window_unload(Window* window);
void main_window_create();

void main_window_destroy(Window* window);
Window* main_window_get_window();
#endif