#pragma once

#include <frc/controller/PIDController.h>
#include <frc/Encoder.h>
#include <frc/SpeedControllerGroup.h>
#include <frc/smartdashboard/SmartDashboard.h>

#include "command/Command.h"
#include "RobotMap.h"
#include "Drivetrain.h"
#include "GlobalConstants.h"

class Drive: public Command {
	private:
		static double P;
		static double I;
		static double D;

	protected:
		const double TOLERANCE_in;

		double numRunCycles = 0;

		static frc2::PIDController pidController;

		Drivetrain *drivetrain = nullptr;

		Drive(Drivetrain *drivetrain, const double TOLERANCE_in);

	public:
		static void InitPID_SD();
		static void ControlPID_SD();
};