#include "command/MoveToPosition.h"

MoveToPosition::MoveToPosition(
frc::SpeedControllerGroup *leftDrive, 
frc::SpeedControllerGroup *rightDrive, 
const double X_in, 
const double Z_in, 
const double FINAL_ANGLE_rad, 
const double LINEAR_TOLERANCE_in, 
const double ANGULAR_TOLERANCE_in) {
	const double ANGLE_rad = (GlobalConstants::PI / 2) - atan2(Z_in, X_in);
	const double LENGTH = sqrt(X_in * X_in + X_in * X_in);
	
	std::vector<Command*> *commands = new std::vector<Command*> {
		new RotateToAngle(leftDrive, rightDrive, ANGLE_rad, ANGULAR_TOLERANCE_in),
		new MoveLength(leftDrive, rightDrive, LENGTH, LINEAR_TOLERANCE_in),
		new RotateToAngle(leftDrive, rightDrive, -ANGLE_rad + FINAL_ANGLE_rad, ANGULAR_TOLERANCE_in)
	};

	commandScheduler = CommandScheduler(commands);
}

void MoveToPosition::Run() {
	if (isFinished) {
		std::cout << "WARNING > CALL TO Run ON FINISHED MoveToPosition" << std::endl;
	}
	else {
		commandScheduler.Run();

		if (commandScheduler.GetIsFinished()) {
			isFinished = true;
		}
	}
}