#include "command/RotateToAngle.h"

RotateToAngle::RotateToAngle(frc::SpeedControllerGroup *leftDrive, frc::SpeedControllerGroup *rightDrive, const double ANGLE_rad, const double TOLERANCE_in): 
Drive(leftDrive, rightDrive, TOLERANCE_in), 
ANGLE_rad(ANGLE_rad) {}

void RotateToAngle::PerformManeuver() {
	if (isFinished) {
		std::cout << "WARNING > CALL TO Run ON FINISHED RotateToAngle" << std::endl;
	}
	else {
		const double ARC_LENGTH_in = 11 * ANGLE_rad;

		const double LEFT_DELTA_DISTANCE_in = leftDriveEncoder.GetDistance() - leftStartDistance_in;
		const double RIGHT_DELTA_DISTANCE_in = rightDriveEncoder.GetDistance() - rightStartDistance_in;

		const double LEFT_SPEED = pidController.Calculate(LEFT_DELTA_DISTANCE_in, ARC_LENGTH_in);
		leftDrive->Set(-LEFT_SPEED);
		
		const double RIGHT_SPEED = pidController.Calculate(RIGHT_DELTA_DISTANCE_in, ARC_LENGTH_in);
		rightDrive->Set(RIGHT_SPEED);

		if (abs(ARC_LENGTH_in - LEFT_DELTA_DISTANCE_in) < TOLERANCE_in && abs(ARC_LENGTH_in - RIGHT_DELTA_DISTANCE_in) < TOLERANCE_in) {
			isFinished = true;
		}
	}
}