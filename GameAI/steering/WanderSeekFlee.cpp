#include "WanderSeekFlee.h"
#include "KinematicUnit.h"
#include "Game.h"

WanderSeekFlee::WanderSeekFlee(KinematicUnit* pMover, KinematicUnit* pTarget, bool shouldFlee)
	:mpMover(pMover),
	mpTarget(pTarget),
	mShouldFlee(shouldFlee)
	{
		mApplyDirectly = true;
	}

<<<<<<< HEAD
Steering* WanderSeekFlee::getSteering () {	
	bool collisionDetected = _collider -> FindClosestTarget ();

	// Collision avoidance:
	if (collisionDetected) {
		//mLinear = _collider -> GetCourseCorrection ();
		mLinear = _collider -> GetCourseCorrection () * mpMover -> getMaxVelocity ();
		mAngular = mpMover -> getOrientationFromVelocity (mpMover -> getOrientation (), mpMover -> getVelocity ());
	}

	// Wander OR Seek/Flee:
	else {
		float xDifference = (mpTarget->getPosition ().getX ()) - (mpMover->getPosition ().getX ());
		float yDifference = (mpTarget->getPosition ().getY ()) - (mpMover->getPosition ().getY ());
		float radiusSquared = (xDifference * xDifference) + (yDifference * yDifference);

		if (radiusSquared < REACTION_RADIUS) {
			// Flee:
			if (mShouldFlee)
				mLinear = mpMover->getPosition () - mpTarget -> getPosition ();

			// Seek:
			else
				mLinear = mpTarget->getPosition () - mpMover -> getPosition ();

			// Since we aren't wandering, the orientation should stay consistent.
			mAngular = mpMover->getOrientationFromVelocity (mpMover->getOrientation (), mpMover->getVelocity ());
		}
=======
Steering* WanderSeekFlee::getSteering () {
	float xDifference =	(mpTarget -> getPosition ().getX ()) - (mpMover -> getPosition ().getX ());
	float yDifference = (mpTarget -> getPosition ().getY ()) - (mpMover -> getPosition ().getY ());
	float radiusSquared = (xDifference * xDifference) + (yDifference * yDifference);

	if (radiusSquared < REACTION_RADIUS) {
		// Flee:
		if (mShouldFlee)
			mLinear = mpMover -> getPosition() - mpTarget -> getPosition();

		// Seek:
		else
			mLinear = mpTarget -> getPosition() - mpMover -> getPosition();

		// Since we aren't wandering, the orientation should stay consistent.
		mAngular = mpMover -> getOrientationFromVelocity (mpMover -> getOrientation (), mpMover -> getVelocity ());
	}
>>>>>>> parent of 687f4b9... Assignment 2 Complete

	// else, wander:
	else {
		mAngular = mpMover -> getOrientation () + (genRandomBinomial () * MAX_WANDER_ROTATION);
		mLinear = mpMover -> getOrientationAsVector () * mpMover -> getMaxVelocity ();
	}

	// We always want to normalize.
	mLinear.normalize();
	mLinear *= mpMover ->getMaxVelocity();
	return this;
}