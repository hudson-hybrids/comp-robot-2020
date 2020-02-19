#include "command/MoveLength.h"

MoveLength::MoveLength(frc::SpeedControllerGroup *leftDrive, frc::SpeedControllerGroup *rightDrive, const double LENGTH_in, const double TOLERANCE_in):
Drive(leftDrive, rightDrive, TOLERANCE_in),
LENGTH_in(LENGTH_in) {}

void MoveLength::PerformManeuver() {
	if (isFinished) {
		std::cout << "WARNING > CALL TO Run ON FINISHED MoveLength" << std::endl;
	}
	else {
		const double LEFT_DELTA_DISTANCE_in = leftDriveEncoder.GetDistance() - leftStartDistance_in;
		const double RIGHT_DELTA_DISTANCE_in = rightDriveEncoder.GetDistance() - rightStartDistance_in;
		
		const double LEFT_SPEED = pidController.Calculate(LEFT_DELTA_DISTANCE_in, LENGTH_in);
		leftDrive->Set(LEFT_SPEED);

		const double RIGHT_SPEED = pidController.Calculate(RIGHT_DELTA_DISTANCE_in, LENGTH_in);
		rightDrive->Set(RIGHT_SPEED);

		if (abs(LENGTH_in - LEFT_DELTA_DISTANCE_in) < TOLERANCE_in && abs(LENGTH_in - RIGHT_DELTA_DISTANCE_in) < TOLERANCE_in) {
			isFinished = true;
		}
	}
}