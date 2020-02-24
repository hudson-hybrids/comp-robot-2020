#include "command/RotateToAngle.h"
#include "Drivetrain.h"

RotateToAngle::RotateToAngle(Drivetrain *drivetrain, const double ANGLE_rad, const double TOLERANCE_in): 
Drive(drivetrain, TOLERANCE_in), 
ANGLE_rad(ANGLE_rad) {}

void RotateToAngle::PerformManeuver() {
	if (isFinished) {
		std::cout << "WARNING > CALL TO Run ON FINISHED RotateToAngle" << std::endl;
	}
	else {
		const double ARC_LENGTH_in = 11 * ANGLE_rad;

		const double LEFT_DELTA_DISTANCE_in = leftDriveEncoder.GetDistance() - leftStartDistance_in;
		const double RIGHT_DELTA_DISTANCE_in = -rightDriveEncoder.GetDistance() - rightStartDistance_in;

		const double LEFT_SPEED = pidController.Calculate(LEFT_DELTA_DISTANCE_in, ARC_LENGTH_in);
		drivetrain->leftDrive.Set(LEFT_SPEED);
		
		const double RIGHT_SPEED = pidController.Calculate(RIGHT_DELTA_DISTANCE_in, ARC_LENGTH_in);
		drivetrain->rightDrive.Set(RIGHT_SPEED);

		std::cout << "Left Speed: " << LEFT_SPEED << "   |   Left Distance: " << LEFT_DELTA_DISTANCE_in << "   |   Right Speed: " << RIGHT_SPEED << "   |   Right Distance: " << RIGHT_DELTA_DISTANCE_in << std::endl;
		
		if (abs(ARC_LENGTH_in - LEFT_DELTA_DISTANCE_in) < TOLERANCE_in && abs(ARC_LENGTH_in - RIGHT_DELTA_DISTANCE_in) < TOLERANCE_in) {
			drivetrain->leftDrive.Set(0);
			drivetrain->rightDrive.Set(0);
			isFinished = true;
		}
	}
}