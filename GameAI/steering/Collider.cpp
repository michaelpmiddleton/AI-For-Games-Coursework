#include "Collider.h"

Collider::Collider (KinematicUnit* character) {
	_thisUnit = character;	
}

bool Collider::FindClosestTarget () {
	bool courseCorrectionRequired = false;

	Vector2D relativePosition;
	Vector2D relativeVelocity;
	float relativeSpeed;
	float timeToCollision;
	float distance;
	float minimumSeparation;

	// Preset the shortestTime to an insanely large number
	float shortestTime = 1000000.0f;

	for (size_t i = 0; i < gpGame -> _um -> GetEnemyCount (); i++) {
		// Calculate the time to collision
		relativePosition = (gpGame -> _um -> GetEnemyUnits ().at (i)-> getPosition ()) - (_thisUnit -> getPosition ());
		relativeVelocity = (gpGame -> _um -> GetEnemyUnits ().at (i) -> getVelocity ()) - (_thisUnit -> getVelocity ());
		relativeSpeed = relativeVelocity.getLength ();
		timeToCollision = ((relativePosition.getX () * relativeVelocity.getX ()) + (relativePosition.getY () * relativeVelocity.getY ())) / (relativeSpeed * relativeSpeed);

		// Check if event is a collision at all
		distance = relativePosition.getLength ();
		minimumSeparation = distance - relativeSpeed * shortestTime;

		if (minimumSeparation > 2 * CollisionRadius)
			continue;

		// Check if it's the shortest (If so, we need to avoid the collision.)
		if (timeToCollision > 0 && timeToCollision < shortestTime) {
			courseCorrectionRequired = true;
			shortestTime = timeToCollision;
			_relativePosition = relativePosition;
			_relativeVelocity = relativeVelocity;
			_closestUnit = gpGame -> _um -> GetEnemyUnits ().at (i);
			_minimumSeparation = minimumSeparation;
			_shortestTime = shortestTime;
			_distance = distance;
		}
	}

	if (courseCorrectionRequired)
		return true;

	else {
		_closestUnit = NULL;
		return false;
	}
}

Vector2D Collider::GetCourseCorrection () {
	// If we're going to hit exactly, or if we're already colliding, then do the steering based on current position
	if (_distance < 2 * CollisionRadius) {
		return (_thisUnit -> getPosition () - _closestUnit -> getPosition ());
	}
	// Otherwise calculate the future relative position
	else {
		return _thisUnit -> getPosition () + _relativeVelocity * _shortestTime;
	}
}

Vector2D Collider::WallCorrection (Vector2D sorryJeff) {
	Vector2D currentTrajectory = _thisUnit -> getPosition () + sorryJeff;
	bool changed = false;

	if (currentTrajectory.getX () > 984) {
		changed = true;
		currentTrajectory.setX (984 - (2 * currentTrajectory.getX () * 0.001f));
	}

	else if (currentTrajectory.getX () < 50) {
		changed = true;
		currentTrajectory.setX (50 - (2 * currentTrajectory.getX () * 0.001f));
	}

	if (currentTrajectory.getY () > 718) {
		changed = true;
		currentTrajectory.setY (718 - (2 * currentTrajectory.getY () * 0.0015f));
	}

	else if (currentTrajectory.getY () < 50) {
		currentTrajectory.setY (50 - (2 * currentTrajectory.getY () * 0.0015f));
		changed = true;
	}

	if (changed)
		return currentTrajectory - _thisUnit -> getPosition ();

	else
		return sorryJeff;
}