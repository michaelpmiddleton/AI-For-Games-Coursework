/*
	FILE:		UnitManager.h
	AUTHOR:		mmiddleton
	DATE:		24 SEP 2017
*/
#ifndef UNITMANAGER_H
#define UNITMANAGER_H

#include <cstdlib>
#include <stdio.h>
#include <vector>
#include <time.h>

#include "KinematicUnit.h"
#include "GraphicsBuffer.h"
#include "Sprite.h"
#include "Vector2D.h"

enum UnitType { seek, arrive, wanderSeek, wanderFlee };

class UnitManager : public Trackable {
	public: 
		UnitManager();											// Constructor

		void Add ();											// Adds a flock at the mouse cursor.
		void Remove ();											// Removes random unit from vector "_units"
		void Update (float updateTime, GraphicsBuffer* gb);		// Calls update on all units.
		bool IsEmpty ();										// Returns true if _units is empty.
		void LoadSprites (Sprite* ps, Sprite* es);				// Get references for Sprites.
		void Init ();											// Create the initial enemies.
		void Clean ();											// Calls the Remove function and deletes the player.
		KinematicUnit* GetPlayerUnit ();						// Returns _player.

	private:
		std::vector<KinematicUnit*> _units;		// Vector containing references to all non-player KU's in game.
		KinematicUnit* _player;					// KU pointer that references player.
		Sprite* _playerSprite;					// Sprite for the player KU.
		Sprite* _enemySprite;					// Sprite for enemy KU's.
};


#endif