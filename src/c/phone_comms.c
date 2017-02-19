#include <pebble.h>
#include "phone_comms.h"

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
void send_message_request(int val){
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
		psleep(1000);
		
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
void in_dropped_handler(AppMessageResult reason, void *context) {	
}

// Called when PebbleKitJS does not acknowledge receipt of a message
void out_failed_handler(DictionaryIterator *failed, AppMessageResult reason, void *context) {
}
