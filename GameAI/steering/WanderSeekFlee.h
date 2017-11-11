#pragma once

#include "Steering.h"

class KinematicUnit;

const float MAX_WANDER_ROTATION = 1.0f;
const float REACTION_RADIUS = 45000.0f;

class WanderSeekFlee : public Steering
{
public:
	WanderSeekFlee (KinematicUnit* pMover, KinematicUnit* pTarget, bool shouldFlee);
	~WanderSeekFlee () {};

	void setTarget (KinematicUnit* pTarget) { mpTarget = pTarget; };

	virtual Steering* getSteering();

private:
	KinematicUnit* mpTarget;
	KinematicUnit* mpMover;
	bool mShouldFlee;
};