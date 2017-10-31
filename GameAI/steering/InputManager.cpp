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
	// Capture mouse state:
	ALLEGRO_MOUSE_STATE mouse;
	al_get_mouse_state (&mouse);

	// Capture keyboard state:
	ALLEGRO_KEYBOARD_STATE keyboard;
	al_get_keyboard_state (&keyboard);

	
	//// Left Mouse Click - Player movement.
	//if (al_mouse_button_down (&mouse, 1)) {
	//	Vector2D position (mouse.x, mouse.y);
	//	GameMessage* playerMovementMessage = new PlayerMoveToMessage (position);
	//	_messageManager -> addMessage (playerMovementMessage, 0);
	//}

	// C key - [DevMode] Select COHESION parameter.
	if (al_key_down (&keyboard, ALLEGRO_KEY_C)) {
		std::cout << "INPUT MANAGER: [DEV] Altering COHESION parameter." << std::endl;
		// TODO
	}

	// S key - [DevMode] Select SEPARATION parameter.
	if (al_key_down (&keyboard, ALLEGRO_KEY_S)) {
		std::cout << "INPUT MANAGER: [DEV] Altering SEPARATION parameter." << std::endl;
		// TODO
	}

	// A key - [DevMode] Select ALIGNMENT parameter.
	if (al_key_down (&keyboard, ALLEGRO_KEY_A)) {
		std::cout << "INPUT MANAGER: [DEV] Altering ALIGNMENT parameter." << std::endl;
		// TODO
	}
	
	// + key - [DevMode] INCREMENT selected parameter.
	if (al_key_down (&keyboard, ALLEGRO_KEY_PAD_PLUS)) {
		std::cout << "INPUT MANAGER: [DEV] INCREMENT selected parameter." << std::endl;
		// TODO
	}

	// - key - [DevMode] DECREMENT selected parameter.
	if (al_key_down (&keyboard, ALLEGRO_KEY_PAD_MINUS)) {
		std::cout << "INPUT MANAGER: [DEV] DECREMET selected parameter." << std::endl;
		// TODO
	}

	// D key - Remove random unit.
	if (al_key_down (&keyboard, ALLEGRO_KEY_D)) {
		std::cout << "INPUT MANAGER: Removing random boid..." << std::endl;
		_unitManager -> Remove ();
	}

	// TAB key - Toggle Dev Mode (Live-edit parameters in-engine)
	if (al_key_down (&keyboard, ALLEGRO_KEY_TAB)) {
		std::cout << "INPUT MANAGER: User has toggled DEV mode." << std::endl;
		GameMessage* gameOverMessage = new GameOverMessage ();
		_messageManager -> addMessage (gameOverMessage, 0);
	}

	// ESC key - Exit game.
	if (al_key_down (&keyboard, ALLEGRO_KEY_ESCAPE)) {
		std::cout << "EXIT GAME!" << std::endl;
		return true;
	}

	_updateMouseText (mouse);
	
	return false;
}

void InputManager::_updateMouseText (ALLEGRO_MOUSE_STATE mouse) {
	//create mouse text
	std::stringstream mousePositionText;
	mousePositionText << "[X: " << mouse.x << ", Y: " << mouse.y << "]";

	//write text at mouse position
	al_draw_text (_allegroFont, al_map_rgb (255, 255, 255), mouse.x, mouse.y, ALLEGRO_ALIGN_CENTRE, mousePositionText.str ().c_str ());

	_graphicsSystem -> swap ();
}