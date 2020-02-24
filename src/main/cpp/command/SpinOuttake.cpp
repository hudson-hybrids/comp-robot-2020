#include "command/SpinOuttake.h"

const double SpinOuttake::S = 0;
const double SpinOuttake::V = 0;
const double SpinOuttake::A = 0;

void SpinOuttake::InitEncoder() {
	const double COUNTS_PER_REV = 360;
	const double WHEEL_DIAMETER_in = 8;
	const double WHEEL_CIRCUMFERENCE = GlobalConstants::PI * WHEEL_DIAMETER_in;
	const double DISTANCE_PER_PULSE = WHEEL_CIRCUMFERENCE / COUNTS_PER_REV;

	outtakeEncoder.SetDistancePerPulse(DISTANCE_PER_PULSE);
}

//frc::SimpleMotorFeedforward<units::inches> SpinOuttake::feedForwardController(S, V, A);
frc::Encoder SpinOuttake::outtakeEncoder(RobotMap::HANG_ENCODER_A, RobotMap::HANG_ENCODER_B);
bool SpinOuttake::encoderInitialized = false;

SpinOuttake::SpinOuttake(WPI_VictorSPX *outtakeMotor, const double TARGET_SPEED_IN_PER_S, const double SPEED_TOLERANCE_IN_PER_S):
TARGET_SPEED_IN_PER_S(TARGET_SPEED_IN_PER_S),
SPEED_TOLERANCE_IN_PER_S(SPEED_TOLERANCE_IN_PER_S) {
	this->outtakeMotor = outtakeMotor;

	if (!encoderInitialized) {
		InitEncoder();
		encoderInitialized = true;
	}
}

void SpinOuttake::Run() {
	const double CURRENT_SPEED_IN_PER_S = outtakeEncoder.GetRate();
}

void SpinOuttake::Stop() {
	outtakeMotor->Set(0);
}