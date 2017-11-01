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

	// SPACE key - [DevMode] Save current state.
	if (al_key_down (&keyboard, ALLEGRO_KEY_SPACE)) {
		GameMessage* saveState = new SaveStateMessage ();
		_messageManager -> addMessage (saveState, 0);
	}


	// C key - [DevMode] Select COHESION parameter.
	if (al_key_down (&keyboard, ALLEGRO_KEY_C)) {
		GameMessage* selectCohesion = new DevModeModificationMessage (SELECT, COHESION);
		_messageManager -> addMessage (selectCohesion, 0);
	}

	// S key - [DevMode] Select SEPARATION parameter.
	if (al_key_down (&keyboard, ALLEGRO_KEY_S)) {
		GameMessage* selectSeparate = new DevModeModificationMessage (SELECT, SEPARATION);
		_messageManager -> addMessage (selectSeparate, 0);
	}

	// A key - [DevMode] Select ALIGNMENT parameter.
	if (al_key_down (&keyboard, ALLEGRO_KEY_A)) {
		GameMessage* selectAlignment = new DevModeModificationMessage (SELECT, ALIGNMENT);
		_messageManager -> addMessage (selectAlignment, 0);
	}
	
	// + key - [DevMode] INCREMENT selected parameter.
	if (al_key_down (&keyboard, ALLEGRO_KEY_PAD_PLUS)) {
		std::cout << "INPUT MANAGER: [DEV] INCREMENT selected parameter." << std::endl;
		GameMessage* incrementSelected = new DevModeModificationMessage (INCREMENT, NONE);
		_messageManager -> addMessage (incrementSelected, 0);
	}

	// - key - [DevMode] DECREMENT selected parameter.
	if (al_key_down (&keyboard, ALLEGRO_KEY_PAD_MINUS)) {
		std::cout << "INPUT MANAGER: [DEV] DECREMET selected parameter." << std::endl;
		GameMessage* decrementSelected = new DevModeModificationMessage (DECREMENT, NONE);
		_messageManager -> addMessage (decrementSelected, 0);
	}

	// D key - Remove random unit.
	if (al_key_down (&keyboard, ALLEGRO_KEY_D)) {
		std::cout << "INPUT MANAGER: Removing random boid..." << std::endl;
		_unitManager -> Remove ();
	}

	// TAB key - Toggle Dev Mode (Live-edit parameters in-engine)
	if (al_key_down (&keyboard, ALLEGRO_KEY_TAB)) {
		GameMessage* toggleDevMode = new DevModeMessage ();
		_messageManager -> addMessage (toggleDevMode, 0);
	}

	// ESC key - Exit game.
	if (al_key_down (&keyboard, ALLEGRO_KEY_ESCAPE)) {
		std::cout << "EXIT GAME!" << std::endl;
		return true;
	}

	_updateMouseGFX (mouse);
	
	return false;
}

void InputManager::_updateMouseGFX (ALLEGRO_MOUSE_STATE mouse) {
	al_draw_filled_circle (mouse.x, mouse.y, 3.0f, al_map_rgb (200, 200, 200));
	_graphicsSystem -> swap ();
}