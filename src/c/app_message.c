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
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "StringSplitting.h"

static Window *s_window;	
char s_menu_data[1024];
char** s_locations;
bool is_weekend;

// Keys for AppMessage Dictionary
// These should correspond to the values you defined in appinfo.json/Settings
enum {
	STATUS_KEY = 0,	
	REQUESTMENU_KEY = 1,
	MENUDATA_KEY = 2,
	MENUSIZE_KEY = 3,
	WEEKEND_KEY = 4
};


// Write message to buffer & send
static void send_message_request(int val){
	APP_LOG(APP_LOG_LEVEL_DEBUG, "send_message called");
	DictionaryIterator *iter;
	
	app_message_outbox_begin(&iter);
	dict_write_uint8(iter, REQUESTMENU_KEY, val);
	
	dict_write_end(iter);
  app_message_outbox_send();
	APP_LOG(APP_LOG_LEVEL_DEBUG, "send_message complete");
}

//Handles Messages from PebbleKit JS (phone) analyzing
void in_received_handler(DictionaryIterator *received, void *context) {
	Tuple *tuple;
	
	tuple = dict_find(received, STATUS_KEY);
	if(tuple) {
		APP_LOG(APP_LOG_LEVEL_DEBUG, "Received Status: %d", (int)tuple->value->uint32);
	}
	
	tuple = dict_find(received, REQUESTMENU_KEY);
	if(tuple) {
		APP_LOG(APP_LOG_LEVEL_DEBUG, "Received Message: %s", tuple->value->cstring);
	}
	
	tuple = dict_find(received, MENUDATA_KEY);
	if(tuple) {
		//strcpy(tuple->value->cstring,s_menu_data);
		APP_LOG(APP_LOG_LEVEL_DEBUG, "Received MenuData: %s", tuple->value->cstring);
		const char delim[2] = "!";
		strcpy(s_menu_data, tuple->value->cstring);
		s_locations = str_split(s_menu_data, delim, 2);
		APP_LOG(APP_LOG_LEVEL_DEBUG, s_locations[1]);
	}
  
	
	tuple = dict_find(received, WEEKEND_KEY);
	if(tuple) {
		//strcpy(tuple->value->cstring,s_menu_data);
		APP_LOG(APP_LOG_LEVEL_DEBUG, "Received weekend: %i", tuple->value->int16);
		is_weekend = tuple->value->int16;
		send_message_request(1);
		
	}
}

// Called when an incoming message from PebbleKitJS is dropped
static void in_dropped_handler(AppMessageResult reason, void *context) {	
}

// Called when PebbleKitJS does not acknowledge receipt of a message
static void out_failed_handler(DictionaryIterator *failed, AppMessageResult reason, void *context) {
}

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