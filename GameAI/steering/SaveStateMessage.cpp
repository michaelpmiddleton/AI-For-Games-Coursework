#include "Game.h"
#include "GameMessageManager.h"
#include "SaveStateMessage.h"

SaveStateMessage::SaveStateMessage () : GameMessage (SAVE_STATE) {}

SaveStateMessage::~SaveStateMessage () {}

void SaveStateMessage::process () {
	std::cout << "Saving to preferences to file........";
	fstream outputFile ("preferences.dat");

	outputFile << std::to_string (gpGame -> CohesionWeight) << "\n";
	outputFile << std::to_string (gpGame -> SeparateWeight) << "\n";
	outputFile << std::to_string (gpGame -> AlignmentWeight) << "\n";

	outputFile.close ();
	std::cout << "DONE!" << std::endl;

}

