#include "command/StopIntake.h"

void StopIntake::Run() {
	if (isFinished) {
		std::cout << "WARNING > CALL TO Run ON FINISHED StopIntake" << std::endl;
	}
	else {
		AutoControl::moveIntake = false;
		isFinished = true;
	}
}