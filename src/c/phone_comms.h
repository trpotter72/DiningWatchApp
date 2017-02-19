#ifndef PHONE_COMMS_H
#define PHONE_COMMS_H
#pragma once

#include <pebble.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "StringSplitting.h"


void send_message_request(int val);

//Handles Messages from PebbleKit JS (phone) analyzing
void in_received_handler(DictionaryIterator *received, void *context);

// Called when an incoming message from PebbleKitJS is dropped
void in_dropped_handler(AppMessageResult reason, void *context);

// Called when PebbleKitJS does not acknowledge receipt of a message
void out_failed_handler(DictionaryIterator *failed, AppMessageResult reason, void *context);

#endif