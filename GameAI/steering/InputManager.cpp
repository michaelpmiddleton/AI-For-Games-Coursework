/*
	FILE:		UnitManager.h
	AUTHOR:		mmiddleton
	DATE:		24 SEP 2017
*/

#include <stdio.h>
#include <allegro5/allegro.h>

#include "Trackable.h"
#include "InputManager.h"

void InputManager::Initialize () {
	al_get_mouse_state (&_mouse);
	al_get_keyboard_state(&_keyboard);
}