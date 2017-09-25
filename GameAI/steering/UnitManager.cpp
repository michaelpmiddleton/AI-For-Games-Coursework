/*
	FILE:		UnitManager.cpp
	AUTHOR:		mmiddleton
	DATE:		24 SEP 2017

*/

#include "UnitManager.h"

UnitManager::UnitManager() {
	_units = std::vector<KinematicUnit*> ();
}

void UnitManager::Init () {
	// Create a player:
	Vector2D pos(0.0f, 0.0f);
	Vector2D vel(0.0f, 0.0f);
	_player = new KinematicUnit(_playerSprite, pos, 1, vel, 0.0f, 200.0f, 10.0f);

	// Create the initial, default units:
	Add (0); // Arrive
	Add (1); // Seek
}

void UnitManager::Add (int type) {
	KinematicUnit* toBeAdded;
	Vector2D position (1000.0f, 500.0f);		// TODO: Player position.
	Vector2D velocity (0.0f, 0.0f);

	switch (type) {
		case 0:
			toBeAdded = new KinematicUnit(_enemySprite, position, 1, velocity, 0.0f, 180.0f, 100.0f);
			toBeAdded -> dynamicArrive (_player);
			break;

		case 1:
			// ERASE:
			position.setX (500.0f);
			position.setY (500.0f);
			// ERASE.
			toBeAdded = new KinematicUnit(_enemySprite, position, 1, velocity, 0.0f, 180.0f, 100.0f);
			toBeAdded -> dynamicSeek (_player);
			break;

		default:
			std::cout << "ERROR: Attempted to add a unit of type " << std::to_string (type) << std::endl;
			break;
	}
	// TODO
}

void UnitManager::Remove () {
	// TODO
}

void UnitManager::Update () {
	// TODO
}

bool UnitManager::IsEmpty () {
	return _units.empty ();
}

void UnitManager::LoadSprites (Sprite* ps, Sprite* es) {
	_playerSprite = ps;
	_enemySprite = es;
}

