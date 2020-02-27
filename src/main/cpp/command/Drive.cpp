#include "command/Drive.h"
#include "Drivetrain.h"

double Drive::P = 0.015;
double Drive::I = 0.0001;
double Drive::D = 0;

frc2::PIDController Drive::pidController(P, I, D);

Drive::Drive(Drivetrain *drivetrain, const double TOLERANCE_in): 
TOLERANCE_in(TOLERANCE_in) {
	this->drivetrain = drivetrain;
}

void Drive::InitPID_SD() {
	frc::SmartDashboard::PutNumber("drivetrain_P", P);
	frc::SmartDashboard::PutNumber("drivetrain_I", I);
	frc::SmartDashboard::PutNumber("drivetrain_D", D);
	frc::SmartDashboard::PutNumber("left_speed", 0);
}

void Drive::ControlPID_SD() {
	P = frc::SmartDashboard::GetNumber("drivetrain_P", P);
	I = frc::SmartDashboard::GetNumber("drivetrain_I", I);
	D = frc::SmartDashboard::GetNumber("drivetrain_D", D);

	pidController.SetP(P);
	pidController.SetI(I);
	pidController.SetD(D);
}