/*

app_message.c

this segment of code is responsible for the portion of the app which will run on the 
Pebble smart watch. Should function as follows:
	Initializes data and window system
	Waits for 'status' message from phone to signal complemetary app is running
	Asks user when they are eating and sends the appropriate request to the phone
	Creates windows and panes from received formatted CSV string
*/

#include <pebble.h>

#include "meal_menu.h"
#include "phone_comms.h"

static Window* s_window;

static void init(void) {
	s_window = window_create();
	window_stack_push(s_window, true);
	
	// Register AppMessage handlers
	app_message_register_inbox_received(in_received_handler); 
	app_message_register_inbox_dropped(in_dropped_handler); 
	app_message_register_outbox_failed(out_failed_handler);

  // Initialize AppMessage inbox and outbox buffers with a suitable size
  const int inbox_size = 2048;
  const int outbox_size = 256;
	app_message_open(inbox_size, outbox_size);
}

static void deinit(void) {
	app_message_deregister_callbacks();
	window_destroy(s_window);
}

int main( void ) {
	init();
	app_event_loop();
	deinit();
}