/*
	FILE:		UnitManager.cpp
	AUTHOR:		mmiddleton
	DATE:		24 SEP 2017

*/

#include "UnitManager.h"

UnitManager::UnitManager () {
	//_units = std::vector<KinematicUnit*> (100); // Start the vector as size of 100. (This should be plenty big enough for the purpose of this assignment.)
	srand (time (NULL)); 
}

void UnitManager::Init () {
	// Initialize random number generator:
	srand (time (NULL));
	
	// Create a player:
	//Vector2D position (200.0f, 200.0f);
	//Vector2D velocity (0.0f, 0.0f);
	//_player = new KinematicUnit(_playerSprite, position, 1, velocity, 0.0f, 200.0f, 10.0f);

	// Create the initial, default units:
	//Add (arrive);
	//Add (wanderSeek);
}

void UnitManager::Add () {
	// TODO
	//_units.push_back ();
}

void UnitManager::Remove () {
	
	if (!_units.empty ()) {
		int index = rand () % _units.size ();
		KinematicUnit* ku = _units.at (index);

		_units.erase (_units.begin () + index);

		delete ku;
		ku = NULL;

	}
}

void UnitManager::Update (float updateTime, GraphicsBuffer* gb) {
	// Update Player & Enemies:
	//_player -> update (updateTime);
	
	for each (KinematicUnit* ku in _units)
		ku -> update (updateTime);
	
	// Draw Player & Enemies:
	//_player->draw(gb);

	for each (KinematicUnit* ku in _units)
		ku->draw(gb);
}

void UnitManager::Clean () {
	// TODO: Clean this up! (ironic...)
	for (KinematicUnit* ku : _units) {
		delete (ku);
		ku = NULL;
	}
	//_units.clear ();		
	

	//delete _player;
	//_player = NULL;
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

std::vector<KinematicUnit*> UnitManager::GetEnemyUnits () {
	return _units;
}

int UnitManager::GetEnemyCount () {
	return _units.size ();
}