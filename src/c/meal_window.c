#include <pebble.h>
#include "meal_window.h"

Window* mainWindow;
MenuLayer* mainMenuLayer;

uint16_t main_get_num_sections_callback(MenuLayer *main_layer, void *data) {
	return menuSize[0];
}

uint16_t main_get_num_rows_callback(MenuLayer *main_layer, uint16_t section_index, void *data) {
    return menuSize[section_index+1];
}

int16_t main_get_header_height_callback(MenuLayer *main_layer, uint16_t section_index, void *data) {
    return MENU_CELL_BASIC_HEADER_HEIGHT;
}

void main_draw_header_callback(GContext* ctx, const Layer *cell_layer, uint16_t section_index, void *data) {
    
}

void main_draw_row_callback(GContext* ctx, const Layer *cell_layer, MenuIndex *cell_index, void *data) {
    
}

void main_select_callback(MenuLayer *main_layer, MenuIndex *cell_index, void *data) {
	
}

void setup_menu_layer(Window *window) {
	Layer *window_layer = window_get_root_layer(window);

    mainMenuLayer = menu_layer_create(GRect(0, 0, 144, 168));
    menu_layer_set_callbacks(mainMenuLayer, NULL, (MenuLayerCallbacks){
        .get_num_sections = main_get_num_sections_callback,
        .get_num_rows = main_get_num_rows_callback,
        .get_header_height = main_get_header_height_callback,
        .draw_header = main_draw_header_callback,
        .draw_row = main_draw_row_callback,
        .select_click = main_select_callback,
    });

    menu_layer_set_click_config_onto_window(mainMenuLayer, window);

    layer_add_child(window_layer, menu_layer_get_layer(mainMenuLayer));
}

void main_window_load(Window* window){
	setup_menu_layer(window);
}

void main_window_unload(Window* window){
	menu_layer_destroy(mainMenuLayer);
}

void main_window_create(){
	mainWindow = window_create();
	window_set_window_handlers(mainWindow,(WindowHandlers){
		.load = main_window_load,
		.unload = main_window_unload
	});
}

void main_window_destroy(Window* window){
	window_destroy(window);
}

Window* main_window_get_window(){
	 return mainWindow;
}