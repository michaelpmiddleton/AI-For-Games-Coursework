#pragma once

#include "GameMessage.h"

class DevModeMessage :public GameMessage
{
public:
	DevModeMessage ();
	~DevModeMessage ();

	void process ();
};