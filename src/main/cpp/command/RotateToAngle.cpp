#include "command/RotateToAngle.h"
#include "Drivetrain.h"

RotateToAngle::RotateToAngle(Drivetrain *drivetrain, const double ANGLE_rad, const double TOLERANCE_in): 
Drive(drivetrain, TOLERANCE_in), 
ANGLE_rad(ANGLE_rad) {}

void RotateToAngle::PerformManeuver() {
	if (isFinished) {
		std::cout << "WARNING > CALL TO PerformManeuver ON FINISHED RotateToAngle" << std::endl;
	}
	else {
		const double ARC_LENGTH_in = 11 * ANGLE_rad;

		const double LEFT_DELTA_DISTANCE_in = leftDistance_in - leftStartDistance_in;
		const double RIGHT_DELTA_DISTANCE_in = rightDistance_in - rightStartDistance_in;

		frc::SmartDashboard::PutNumber("target_length", ARC_LENGTH_in);
		frc::SmartDashboard::PutNumber("left_distance", LEFT_DELTA_DISTANCE_in);
		frc::SmartDashboard::PutNumber("right_distance", RIGHT_DELTA_DISTANCE_in);

		const double LEFT_SPEED = pidController.Calculate(LEFT_DELTA_DISTANCE_in, ARC_LENGTH_in);
		drivetrain->leftDrive.PIDWrite(LEFT_SPEED);
		
		const double RIGHT_SPEED = pidController.Calculate(RIGHT_DELTA_DISTANCE_in, ARC_LENGTH_in);
		drivetrain->rightDrive.PIDWrite(RIGHT_SPEED);
		
		if (abs(ARC_LENGTH_in - LEFT_DELTA_DISTANCE_in) < TOLERANCE_in && abs(ARC_LENGTH_in - RIGHT_DELTA_DISTANCE_in) < TOLERANCE_in) {
			drivetrain->leftDrive.Set(0);
			drivetrain->rightDrive.Set(0);
			isFinished = true;
		}
	}
}