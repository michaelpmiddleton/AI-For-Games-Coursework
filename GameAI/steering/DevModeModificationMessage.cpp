#include "Game.h"
#include "GameMessageManager.h"
#include "DevModeModificationMessage.h"

DevModeModificationMessage::DevModeModificationMessage (const ModificationCommand command, const ModificationParameter parameter)
	: GameMessage (DEV_MODE_ACTION),
	_command (command),
	_parameter (parameter){}

DevModeModificationMessage::~DevModeModificationMessage () {}

void DevModeModificationMessage::process () {
	switch (_command) {
		case INCREMENT:
			gpGame -> AdjustParameter (1);
			break;

		case DECREMENT:
			gpGame -> AdjustParameter (-1);
			break;

		case SELECT:
			gpGame -> ToggleSelectedParameter (_parameter);
			break;

		default:
			std::cout << "ERROR: Unsupported command type." << std::endl;
			break;
	}
}

