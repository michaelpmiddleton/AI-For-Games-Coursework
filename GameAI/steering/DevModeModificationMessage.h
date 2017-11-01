#pragma once

#include "GameMessage.h"

class Vector2D;

enum ModificationCommand {
	INCREMENT,
	DECREMENT,
	SELECT
};

enum ModificationParameter {
	NONE,
	ALIGNMENT,
	COHESION,
	SEPARATION
};

class DevModeModificationMessage : public GameMessage {
	public:
		DevModeModificationMessage (ModificationCommand command, ModificationParameter parameter);
		~DevModeModificationMessage ();

		void process ();

	private:
		ModificationCommand _command;
		ModificationParameter _parameter;
};