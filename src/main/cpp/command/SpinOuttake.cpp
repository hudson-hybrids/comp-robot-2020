#include "command/SpinOuttake.h"

SpinOuttake::SpinOuttake(can::WPI_TalonSRX *outtakeMotor_Talon, can::WPI_VictorSPX *outtakeMotor_Victor) {
	this->outtakeMotor_Talon = outtakeMotor_Talon;
	this->outtakeMotor_Victor = outtakeMotor_Victor;
}

void SpinOuttake::SetSpeed(double targetSpeed_RPM) {
	targetSpeed_unitsPer100ms = targetSpeed_RPM * 4096 / 600;
}

void SpinOuttake::Run() {
	outtakeMotor_Talon->Set(ControlMode::Velocity, targetSpeed_unitsPer100ms);
	double talonCurrent = outtakeMotor_Talon->GetOutputCurrent();
	outtakeMotor_Victor->Set(ControlMode::Current, talonCurrent);
}

void SpinOuttake::Stop() {
	outtakeMotor_Talon->Set(0);
	outtakeMotor_Victor->Set(0);
}