/*
	FILE:		UnitManager.cpp
	AUTHOR:		mmiddleton
	DATE:		24 SEP 2017

*/

#include "UnitManager.h"

UnitManager::UnitManager() {
	//_units = std::vector<KinematicUnit*> (100); // Start the vector as size of 100. (This should be plenty big enough for the purpose of this assignment.)
	srand (time (NULL)); 
}

void UnitManager::Init () {
	// Create a player:
	Vector2D position (200.0f, 200.0f);
	Vector2D velocity (0.0f, 0.0f);
	_player = new KinematicUnit(_playerSprite, position, 1, velocity, 0.0f, 200.0f, 10.0f);

	// Create the initial, default units:
	Add (arrive);
	Add (seek);
}

void UnitManager::Add (UnitType type) {
	KinematicUnit* toBeAdded;
	Vector2D position = _player -> getPosition ();		// TODO: Player position.
	Vector2D velocity (0.0f, 0.0f);

	switch (type) {
		case seek:
			if (position.getX () > 200.0f)
				position.setX (position.getX () - 200.0f);

			else
				position.setX(position.getX() + 200.0f);

			toBeAdded = new KinematicUnit (_enemySprite, position, 1, velocity, 0.0f, 180.0f, 100.0f);
			toBeAdded -> dynamicArrive (_player);
			break;

		case arrive:
			if (position.getY () > 100.0f)
				position.setY (position.getY () - 100.0f);
	
			else
				position.setY (position.getY () + 100.0f);
		
			toBeAdded = new KinematicUnit (_enemySprite, position, 1, velocity, 0.0f, 180.0f, 100.0f);
			toBeAdded -> dynamicSeek (_player);
			break;

		default:
			std::cout << "ERROR: Attempted to add a unit of type " << std::to_string (type) << std::endl;
			break;
	}

	_units.push_back (toBeAdded);
}

void UnitManager::Remove () {
	int index = rand () % _units.size ();
	KinematicUnit* ku = _units.at (index);
	
	delete ku;
	ku = NULL;

	_units.erase (_units.begin () + index);
}

void UnitManager::Update (float updateTime, GraphicsBuffer* gb) {
	// Update Player & Enemies:
	_player -> update (updateTime);
	
	for each (KinematicUnit* ku in _units)
		ku -> update (updateTime);
	
	// Draw Player & Enemies:
	_player->draw(gb);

	for each (KinematicUnit* ku in _units)
		ku->draw(gb);
}

void UnitManager::Clean () {
	while (!_units.empty ()) {
		KinematicUnit* ku = _units.back ();
		delete ku;
		ku = NULL;
		_units.pop_back ();
	}

	delete _player;
	_player = NULL;
}

bool UnitManager::IsEmpty () {
	return _units.empty ();
}

void UnitManager::LoadSprites (Sprite* ps, Sprite* es) {
	_playerSprite = ps;
	_enemySprite = es;
}

KinematicUnit* UnitManager::GetPlayerUnit () {
	return _player;
}
