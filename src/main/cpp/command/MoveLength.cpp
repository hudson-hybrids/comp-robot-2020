#include "command/MoveLength.h"

MoveLength::MoveLength(Drivetrain *drivetrain, const double LENGTH_in, const double TOLERANCE_in):
Drive(drivetrain, TOLERANCE_in),
LENGTH_in(LENGTH_in) {}

void MoveLength::Run() {
	if (isFinished) {
		std::cout << "WARNING > CALL TO Run ON FINISHED MoveLength" << std::endl;
	}
	else {
		if (!startDistanceFound) {
			leftStart = -drivetrain->leftEncoder.GetDistance();
			rightStart = drivetrain->rightEncoder.GetDistance();
			startDistanceFound = true;
		}
		double leftDistance = -drivetrain->leftEncoder.GetDistance();
		double rightDistance = drivetrain->rightEncoder.GetDistance();

		const double LEFT_DELTA_DISTANCE_in = leftDistance - leftStart;
		const double RIGHT_DELTA_DISTANCE_in = rightDistance - rightStart;

		frc::SmartDashboard::PutNumber("target_length", LENGTH_in);
		frc::SmartDashboard::PutNumber("left_distance", LEFT_DELTA_DISTANCE_in);
		frc::SmartDashboard::PutNumber("right_distance", RIGHT_DELTA_DISTANCE_in);

		const double LEFT_SPEED = pidController.Calculate(LEFT_DELTA_DISTANCE_in, LENGTH_in);
		drivetrain->leftDrive.PIDWrite(LEFT_SPEED);

		const double RIGHT_SPEED = pidController.Calculate(RIGHT_DELTA_DISTANCE_in, LENGTH_in);
		drivetrain->rightDrive.PIDWrite(LEFT_SPEED);

		frc::SmartDashboard::PutNumber("left_speed", LEFT_SPEED);

		if (abs(LENGTH_in - LEFT_DELTA_DISTANCE_in) < TOLERANCE_in/* && abs(LENGTH_in - RIGHT_DELTA_DISTANCE_in) < TOLERANCE_in*/) {
			drivetrain->leftDrive.Set(0);
			drivetrain->rightDrive.Set(0);
			isFinished = true;
		}
	}
}