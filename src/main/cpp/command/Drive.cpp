#include "command/Drive.h"

const double Drive::P = 0;
const double Drive::I = 0;
const double Drive::D = 0;

void Drive::InitEncoders() {
	const double COUNTS_PER_REV = 360;
	const double WHEEL_DIAMETER_in = 4;
	const double WHEEL_CIRCUMFERENCE = GlobalConstants::PI * WHEEL_DIAMETER_in;
	const double DISTANCE_PER_PULSE = WHEEL_CIRCUMFERENCE / COUNTS_PER_REV;

	leftDriveEncoder.SetDistancePerPulse(DISTANCE_PER_PULSE);
	rightDriveEncoder.SetDistancePerPulse(DISTANCE_PER_PULSE);

	leftStartDistance_in = leftDriveEncoder.GetDistance();
	rightStartDistance_in = rightDriveEncoder.GetDistance();
}

frc2::PIDController Drive::pidController(P, I, D);
frc::Encoder Drive::leftDriveEncoder(RobotMap::LEFT_DRIVE_ENCODER_A, RobotMap::LEFT_DRIVE_ENCODER_B);
frc::Encoder Drive::rightDriveEncoder(RobotMap::RIGHT_DRIVE_ENCODER_A, RobotMap::RIGHT_DRIVE_ENCODER_B);
bool Drive::encodersInitialized = false;

Drive::Drive(frc::SpeedControllerGroup *leftDrive, frc::SpeedControllerGroup *rightDrive, const double TOLERANCE_in): 
TOLERANCE_in(TOLERANCE_in) {
	this->leftDrive = leftDrive;
	this->rightDrive = rightDrive;
}

void Drive::Run() {
	if (!encodersInitialized) {
		InitEncoders();
	}

	PerformManeuver();
}