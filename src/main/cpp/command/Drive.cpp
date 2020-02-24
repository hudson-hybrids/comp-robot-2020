#include "command/Drive.h"
#include "Drivetrain.h"

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
}

frc2::PIDController Drive::pidController(P, I, D);
frc::Encoder Drive::leftDriveEncoder(RobotMap::LEFT_DRIVE_ENCODER_A, RobotMap::LEFT_DRIVE_ENCODER_B);
frc::Encoder Drive::rightDriveEncoder(RobotMap::RIGHT_DRIVE_ENCODER_A, RobotMap::RIGHT_DRIVE_ENCODER_B);
bool Drive::encodersInitialized = false;
double Drive::leftDistance_in = 0;
double Drive::rightDistance_in = 0;

Drive::Drive(Drivetrain *drivetrain, const double TOLERANCE_in): 
TOLERANCE_in(TOLERANCE_in) {
	this->drivetrain = drivetrain;

	if (!encodersInitialized) {
		InitEncoders();
		encodersInitialized = true;
	}
}

void Drive::Run() {
	Drive::leftDistance_in = leftDriveEncoder.GetDistance();
	Drive::rightDistance_in = -rightDriveEncoder.GetDistance();

	if (!startDistancesCalculated) {
		leftStartDistance_in = leftDistance_in;
		leftStartDistance_in = rightDistance_in;
		startDistancesCalculated = true;
	}

	PerformManeuver();
}