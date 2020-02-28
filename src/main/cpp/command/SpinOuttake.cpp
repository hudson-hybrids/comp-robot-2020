#include "command/SpinOuttake.h"

SpinOuttake::SpinOuttake(can::WPI_TalonSRX *outtakeMotor_Talon, can::WPI_VictorSPX *outtakeMotor_Victor) {
	this->outtakeMotor_Talon = outtakeMotor_Talon;
	this->outtakeMotor_Victor = outtakeMotor_Victor;
}

SpinOuttake::SpinOuttake(can::WPI_TalonSRX *outtakeMotor_Talon, can::WPI_VictorSPX *outtakeMotor_Victor, double targetSpeed_RPM) {
	this->outtakeMotor_Talon = outtakeMotor_Talon;
	this->outtakeMotor_Victor = outtakeMotor_Victor;
	SetSpeed(targetSpeed_RPM);
}

void SpinOuttake::SetSpeed(double targetSpeed_RPM) {
	ResetTimer();
	this->targetSpeed_RPM = targetSpeed_RPM;
	targetSpeed_unitsPer100ms = targetSpeed_RPM * 4096 / 600;
}

void SpinOuttake::ResetTimer() {
	timer.Reset();
	timer.Stop();
	timerStarted = false;
}

void SpinOuttake::Run() {
	if (!timerStarted) {
		timer.Start();
		timerStarted = true;
	}

	frc::SmartDashboard::PutNumber("outtake_velocity", targetSpeed_RPM);

	outtakeMotor_Talon->SetInverted(false);
	outtakeMotor_Talon->Set(ControlMode::Velocity, targetSpeed_unitsPer100ms);
	outtakeMotor_Victor->SetInverted(InvertType::OpposeMaster);
	outtakeMotor_Victor->Follow(*outtakeMotor_Talon);

	if (timer.Get() > 3) {
		isFinished = true;
	}
}

void SpinOuttake::Stop() {
	outtakeMotor_Talon->Set(0);
	outtakeMotor_Victor->Set(0);
}