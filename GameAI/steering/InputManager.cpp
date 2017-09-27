/*
	FILE:		UnitManager.h
	AUTHOR:		mmiddleton
	DATE:		24 SEP 2017
*/

#include "InputManager.h"


void InputManager::Initialize () {
	
}

void InputManager::LoadAssets (GameMessageManager* gmm, GraphicsSystem* gs, ALLEGRO_FONT* af, UnitManager* um) {
	_messageManager = gmm;
	_graphicsSystem = gs;
	_allegroFont = af;
	_unitManager = um;
}

bool InputManager::ProcessInput () {
	bool gameOverToggle = false;
	
	// Capture mouse state:
	ALLEGRO_MOUSE_STATE mouse;
	al_get_mouse_state (&mouse);

	// Capture keyboard state:
	ALLEGRO_KEYBOARD_STATE keyboard;
	al_get_keyboard_state (&keyboard);

	
	// Left Mouse Click - Player movement.
	if (al_mouse_button_down (&mouse, 1)) {
		Vector2D position (mouse.x, mouse.y);
		GameMessage* playerMovementMessage = new PlayerMoveToMessage (position);
		_messageManager -> addMessage (playerMovementMessage, 0);
	}

	// A key - Add ARRIVE unit.
	if (al_key_down (&keyboard, ALLEGRO_KEY_A)) {
		std::cout << "INPUT MANAGER: Adding ARRIVE Unit." << std::endl;
		_unitManager -> Add (arrive);
	}

	// S key - Add ARRIVE unit.
	if (al_key_down (&keyboard, ALLEGRO_KEY_S)) {
		std::cout << "INPUT MANAGER: Adding SEEK Unit." << std::endl;
		_unitManager -> Add(seek);
	}

	// D key - Remove random unit.
	if (al_key_down(&keyboard, ALLEGRO_KEY_D)) {
		std::cout << "INPUT MANAGER: Removing random unit..." << std::endl;
		_unitManager -> Remove ();
	}

	// ESC key - Exit game.
	if (al_key_down (&keyboard, ALLEGRO_KEY_ESCAPE)) {
		std::cout << "EXIT GAME!" << std::endl;
		gameOverToggle = true;
	}

	_updateMouseText (mouse);
	
	return gameOverToggle;
}

void InputManager::_updateMouseText (ALLEGRO_MOUSE_STATE mouse) {
	//create mouse text
	std::stringstream mousePositionText;
	mousePositionText << "[X: " << mouse.x << ", Y: " << mouse.y << "]";

	//write text at mouse position
	al_draw_text (_allegroFont, al_map_rgb (255, 255, 255), mouse.x, mouse.y, ALLEGRO_ALIGN_CENTRE, mousePositionText.str ().c_str ());

	_graphicsSystem -> swap ();
}