#include "command/Drive.h"

frc::Encoder Drive::leftDriveEncoder{RobotMap::LEFT_DRIVE_ENCODER_A, RobotMap::LEFT_DRIVE_ENCODER_B};
frc::Encoder Drive::rightDriveEncoder{RobotMap::RIGHT_DRIVE_ENCODER_A, RobotMap::RIGHT_DRIVE_ENCODER_B};

Drive::Drive(const double P, const double I, const double D) {
	pidController = frc2::PIDController(P, I, D);
}

void Drive::InitEncoders() {
	const double COUNTS_PER_REV = 360;
	const double WHEEL_DIAMETER_in = 4;
	const double WHEEL_CIRCUMFERENCE = GlobalConstants::PI * WHEEL_DIAMETER_in;
	const double DISTANCE_PER_PULSE = WHEEL_CIRCUMFERENCE / COUNTS_PER_REV;

	leftDriveEncoder.SetDistancePerPulse(DISTANCE_PER_PULSE);
	rightDriveEncoder.SetDistancePerPulse(DISTANCE_PER_PULSE);
}