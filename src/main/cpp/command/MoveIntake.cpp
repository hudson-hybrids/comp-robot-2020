#include "command/MoveIntake.h"

void MoveIntake::Run() {
	if (isFinished) {
		std::cout << "WARNING > CALL TO Run ON FINISHED MoveIntake" << std::endl;
	}
	else {
		AutoControl::moveIntake = true;
		isFinished = true;
	}
}