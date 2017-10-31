/*
	FILE:		InputManager.h
	AUTHOR:		mmiddleton
	DATE:		25 SEP 2017
*/
#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include <stdio.h>
#include <sstream>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>


#include "Defines.h"
#include "GraphicsSystem.h"
#include "GameMessageManager.h"
#include "PlayerMoveToMessage.h"
#include "GameOverMessage.h"

#include "Vector2D.h"
#include "UnitManager.h"
#include "Trackable.h"

class InputManager : public Trackable {
	public:
		void Initialize ();								// Initialize needed components.
		void LoadAssets (GameMessageManager* gmm,
			GraphicsSystem* gs,
			ALLEGRO_FONT* af,
			UnitManager* um);							// Pulls in the Game object's GameMessageManager to send them. 
		bool ProcessInput ();							// Checks for input from keyboard/mouse.

	private:
		GameMessageManager* _messageManager;
		GraphicsSystem* _graphicsSystem;
		ALLEGRO_FONT* _allegroFont;
		UnitManager* _unitManager;

		void _updateMouseText(ALLEGRO_MOUSE_STATE mouse);					// Updates the string denoting mouse position on the bottom 

};

#endif