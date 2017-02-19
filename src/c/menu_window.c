#include <pebble.h>
#include "menu_window.h"
#include "phone_comms.h"

Window* menuWindow;
MenuLayer* menuMenuLayer;
int timeOfDay;
uint16_t menu_get_num_sections_callback(MenuLayer *main_layer, void *data) {
	return 3;
}

uint16_t menu_get_num_rows_callback(MenuLayer *main_layer, uint16_t section_index, void *data) {
    switch(section_index){
			case 0:
				return 3;
			case 1:
				return 1;
			case 2:
				return 2;
		}
	return 0;
}

int16_t menu_get_header_height_callback(MenuLayer *main_layer, uint16_t section_index, void *data) {
    return MENU_CELL_BASIC_HEADER_HEIGHT + 5;
}

void menu_draw_header_callback(GContext* ctx, const Layer *cell_layer, uint16_t section_index, void *data) {
	   switch(section_index){
			case 0:
				menu_cell_basic_header_draw(ctx, cell_layer, "Daisy Hill Grill");
			 break;
			case 1:
				menu_cell_basic_header_draw(ctx, cell_layer, "Lenore's Classics");
			 break;
			case 2:
			 menu_cell_basic_header_draw(ctx, cell_layer, "Nature's Finest");
			 break;
		}
    
}

void menu_draw_row_callback(GContext* ctx, const Layer *cell_layer, MenuIndex *cell_index, void *data) {
	switch (cell_index->row) {
        case 0:
          menu_cell_basic_draw(ctx, cell_layer, "Food", NULL, NULL);
          break;
        case 1:
          // This is a basic menu icon with a cycling icon
          menu_cell_basic_draw(ctx, cell_layer, "Food", NULL, NULL);
          break;
        case 2: 
          {
					menu_cell_basic_draw(ctx, cell_layer, "Food",NULL , NULL);
          }
          break;
      }
    
}

void menu_select_callback(MenuLayer *main_layer, MenuIndex *cell_index, void *data) {
	switch (cell_index->row) {
    // This is the menu item with the cycling icon
    case 0:
      // Cycle the icon
 			send_message_request(0);
      break;
		case 1:
			send_message_request(2);
			break;
		case 2:
			send_message_request(3);
			break;
  }
}

void setup_menu1_layer(Window *window) {
	Layer *window_layer = window_get_root_layer(window);

    menuMenuLayer = menu_layer_create(GRect(0, 0, 144, 168));
    menu_layer_set_callbacks(menuMenuLayer, NULL, (MenuLayerCallbacks){
        .get_num_sections = menu_get_num_sections_callback,
        .get_num_rows = menu_get_num_rows_callback,
        .get_header_height = menu_get_header_height_callback,
        .draw_header = menu_draw_header_callback,
        .draw_row = menu_draw_row_callback,
        .select_click = menu_select_callback,
    });

    menu_layer_set_click_config_onto_window(menuMenuLayer, window);

    layer_add_child(window_layer, menu_layer_get_layer(menuMenuLayer));
}

void menu_window_load(Window* window){
	setup_menu1_layer(window);
}

void menu_window_unload(Window* window){
	menu_layer_destroy(menuMenuLayer);
}

void menu_window_create(int val){
	menuWindow = window_create();
	window_set_window_handlers(menuWindow,(WindowHandlers){
		.load = menu_window_load,
		.unload = menu_window_unload
	});
	timeOfDay = val;
}

void menu_window_destroy(Window* window){
	window_destroy(window);
}

Window* menu_window_get_window(){
	 return menuWindow;
}