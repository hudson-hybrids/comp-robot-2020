#include "command/Drive.h"
#include "Drivetrain.h"

double Drive::P = 0.015;
double Drive::I = 0;
double Drive::D = 0;

frc2::PIDController Drive::pidController(P, I, D);
double Drive::leftDistance_in = 0;
double Drive::rightDistance_in = 0;

Drive::Drive(Drivetrain *drivetrain, const double TOLERANCE_in): 
TOLERANCE_in(TOLERANCE_in) {
	this->drivetrain = drivetrain;
}

void Drive::Run() {
	Drive::leftDistance_in = -drivetrain->leftEncoder.GetDistance();
	Drive::rightDistance_in = -drivetrain->rightEncoder.GetDistance();

	if (!startDistancesCalculated) {
		leftStartDistance_in = leftDistance_in;
		leftStartDistance_in = rightDistance_in;
		startDistancesCalculated = true;
	}

	PerformManeuver();
}

void Drive::InitPID_SD() {
	frc::SmartDashboard::PutNumber("drivetrain_P", P);
	frc::SmartDashboard::PutNumber("drivetrain_I", I);
	frc::SmartDashboard::PutNumber("drivetrain_D", D);
}

void Drive::ControlPID_SD() {
	P = frc::SmartDashboard::GetNumber("drivetrain_P", P);
	I = frc::SmartDashboard::GetNumber("drivetrain_I", I);
	D = frc::SmartDashboard::GetNumber("drivetrain_D", D);
}