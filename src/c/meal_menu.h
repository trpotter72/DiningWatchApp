#ifndef MEAL_MENU_H
#define MEAL_MENU_H
#pragma once
#include "phone_comms.h"

void meal_window_create(bool is_weekend);
void meal_window_destroy();
Window* meal_window_get_level();

#endif