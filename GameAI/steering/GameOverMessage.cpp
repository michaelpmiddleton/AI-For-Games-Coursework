#include "Game.h"
#include "KinematicUnit.h"
#include "GameMessageManager.h"
#include "GameOverMessage.h"

GameOverMessage::GameOverMessage () :GameMessage (GAME_OVER_MESSAGE) {}

GameOverMessage::~GameOverMessage () {}

void GameOverMessage::process () {
	gpGame -> ToggleDevMode ();
}

