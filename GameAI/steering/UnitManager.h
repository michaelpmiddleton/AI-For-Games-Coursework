/*
	FILE:		UnitManager.h
	AUTHOR:		mmiddleton
	DATE:		24 SEP 2017

	
*/
#ifndef UNITMANAGER_H
#define UNITMANAGER_H

#include <stdio.h>
#include <vector>

#include "KinematicUnit.h"
#include "GraphicsBuffer.h"
#include "Sprite.h"
#include "Vector2D.h"




class UnitManager : public Trackable {
	UnitManager ();
	
	public: 
		void Add (int type);						// Adds a unit 200 pixels away from player. (0 = Arrive, 1 = Seek)
		void Remove ();								// Removes random unit from vector "_units"
		void Update ();								// Calls update on all units.
		bool IsEmpty ();							// Returns true if _units is empty.
		void LoadSprites (Sprite* ps, Sprite* es);	// Get references for Sprites.
		void Init ();								// Create the initial enemies.

	private:
		std::vector<KinematicUnit*> _units;		// Vector containing references to all non-player KU's in game.
		KinematicUnit* _player;					// KU pointer that references player.
		Sprite* _playerSprite;
		Sprite* _enemySprite;
};
#endif