#include "Game.h"
#include "GameMessageManager.h"
#include "DevModeMessage.h"

DevModeMessage::DevModeMessage () : GameMessage (DEV_MODE_TOGGLE) {}

DevModeMessage::~DevModeMessage () {}

void DevModeMessage::process () {
	gpGame -> ToggleDevMode ();
}

