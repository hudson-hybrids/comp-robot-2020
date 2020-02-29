#include "command/SpinOuttake.h"

void SpinOuttake::Run(can::WPI_TalonSRX *outtakeMotor_Talon, can::WPI_VictorSPX *outtakeMotor_Victor, double targetSpeed_unitsPer100ms) {
	frc::SmartDashboard::PutNumber("outtake_velocity", outtakeMotor_Talon->GetSelectedSensorVelocity());
	frc::SmartDashboard::PutNumber("outtake_percent", outtakeMotor_Talon->GetMotorOutputPercent());

	//outtakeMotor_Talon->SetInverted(false);
	outtakeMotor_Talon->Set(ControlMode::Velocity, targetSpeed_unitsPer100ms);
	//outtakeMotor_Victor->Set(ControlMode::PercentOutput, -outtakeMotor_Talon->GetMotorOutputPercent);
	outtakeMotor_Victor->SetInverted(InvertType::OpposeMaster);
	outtakeMotor_Victor->Follow(*outtakeMotor_Talon);
}

void SpinOuttake::Stop(can::WPI_TalonSRX *outtakeMotor_Talon, can::WPI_VictorSPX *outtakeMotor_Victor) {
	outtakeMotor_Talon->Set(0);
	outtakeMotor_Victor->Set(0);
}