#pragma once

#include "Game.h"
#include "KinematicUnit.h"

/*
	Collider class is a light-weight version of Unity's class of the same name. It has the following functionality:
		+ 

*/

class Collider : public Trackable {
	public:
		Collider (KinematicUnit* _character);
		bool FindClosestTarget ();						// Sets _closestUnit to the proper corresponding unit or to null. Returns true if a collision is detected.
		Vector2D GetCourseCorrection ();				// Returns a Vector2D for the KinematicUnit to use in getSteering ().
		Vector2D WallCorrection (Vector2D sorryJeff);	// Detects walls and corrects course based on their position.

		float CollisionRadius = 100.0f;					// All units have a hard-coded collision radius.


	private:
		KinematicUnit* _thisUnit;
		KinematicUnit* _closestUnit;
		Vector2D _relativePosition;
		Vector2D _relativeVelocity;
		float _minimumSeparation;
		float _shortestTime;
		float _distance;

};