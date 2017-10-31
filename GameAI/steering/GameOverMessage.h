#pragma once

#include "GameMessage.h"

class Vector2D;

class GameOverMessage :public GameMessage
{
public:
	GameOverMessage ();
	~GameOverMessage ();

	void process ();
};