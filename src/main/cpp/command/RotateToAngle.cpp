#include "command/RotateToAngle.h"

RotateToAngle::RotateToAngle(const double P, const double I, const double D) {
	
}

void RotateToAngle::Run() override {
	const double LEFT_START_DISTANCE_in = leftDriveEncoder.GetDistance();
	const double RIGHT_START_DISTANCE_in = rightDriveEncoder.GetDistance();

	const double ARC_LENGTH_in = 11 * angle;

	while (true) {
		const double LEFT_DELTA_DISTANCE_in = leftDriveEncoder.GetDistance() - LEFT_START_DISTANCE_in;
		const double RIGHT_DELTA_DISTANCE_in = rightDriveEncoder.GetDistance() - RIGHT_START_DISTANCE_in;

		if (abs(ARC_LENGTH_in - LEFT_DELTA_DISTANCE_in) < tolerance && abs(ARC_LENGTH_in - RIGHT_DELTA_DISTANCE_in) < tolerance) {
			break;
		}

		const double LEFT_SPEED = pidController->Calculate(LEFT_DELTA_DISTANCE_in, ARC_LENGTH_in);
		leftGroup.Set(-LEFT_SPEED);
		const double RIGHT_SPEED = pidController->Calculate(RIGHT_DELTA_DISTANCE_in, ARC_LENGTH_in);
		rightGroup.Set(RIGHT_SPEED);
	}
}