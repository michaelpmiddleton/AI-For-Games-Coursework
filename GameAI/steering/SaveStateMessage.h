#pragma once

#include "GameMessage.h"
#include <fstream>
#include <iostream>

class SaveStateMessage :public GameMessage
{
public:
	SaveStateMessage ();
	~SaveStateMessage ();

	void process ();
};