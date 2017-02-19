#include <pebble.h>
#include "meal_window.h"
#include "phone_comms.h"
#include "menu_window.h"

Window* mainWindow;
MenuLayer* mainMenuLayer;

uint16_t main_get_num_sections_callback(MenuLayer *main_layer, void *data) {
	return 1;
}

uint16_t main_get_num_rows_callback(MenuLayer *main_layer, uint16_t section_index, void *data) {
    return 3;
}

int16_t main_get_header_height_callback(MenuLayer *main_layer, uint16_t section_index, void *data) {
    return MENU_CELL_BASIC_HEADER_HEIGHT;
}

void main_draw_header_callback(GContext* ctx, const Layer *cell_layer, uint16_t section_index, void *data) {
	menu_cell_basic_header_draw(ctx, cell_layer, "Mrs.E's Dining Center");
    
}

void main_draw_row_callback(GContext* ctx, const Layer *cell_layer, MenuIndex *cell_index, void *data) {
	switch (cell_index->row) {
        case 0:
          // This is a basic menu item with a title and subtitle
          menu_cell_basic_draw(ctx, cell_layer, "Breakfast", "7 a.m. - 11 a.m.", NULL);
          break;
        case 1:
          // This is a basic menu icon with a cycling icon
          menu_cell_basic_draw(ctx, cell_layer, "Lunch", "11 a.m. - 4 p.m.", NULL);
          break;
        case 2: 
          {
					menu_cell_basic_draw(ctx, cell_layer, "Dinner", "4 p.m. - 7 p.m.", NULL);
          }
          break;
      }
    
}

void main_select_callback(MenuLayer *main_layer, MenuIndex *cell_index, void *data) {
	switch (cell_index->row) {
    // This is the menu item with the cycling icon
    case 0:
      // Cycle the icon
 			send_message_request(0);
			menu_window_create(cell_index->row);
			window_stack_push(menu_window_get_window(), true);
      break;
		case 1:
		//	send_message_request(2);
			menu_window_create(cell_index->row);
			window_stack_push(menu_window_get_window(), true);
			break;
		case 2:
			send_message_request(3);
			menu_window_create(cell_index->row);
			window_stack_push(menu_window_get_window(), true);
			break;
  }
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