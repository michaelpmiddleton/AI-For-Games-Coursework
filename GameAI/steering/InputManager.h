/*
	FILE:		InputManager.h
	AUTHOR:		mmiddleton
	DATE:		25 SEP 2017
*/
#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

class InputManager {
	public:
		InputManager ();			// Constructor

		void Initialize ();			// Initialize needed components.
		void LoadAssets ();			// Pulls in 
		void ProcessInput ();		// Checks for input from keyboard/mouse.

		std::stringstream GetMousePosition ();		// Return mouse position string.

	private:
		ALLEGRO_MOUSE_STATE _mouse;
		ALLEGRO_KEYBOARD_STATE _keyboard;

};

#endif