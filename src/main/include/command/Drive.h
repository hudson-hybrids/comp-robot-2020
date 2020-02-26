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

		static frc2::PIDController pidController;

		static double leftDistance_in;
		static double rightDistance_in;

		Drivetrain *drivetrain = nullptr;

		double leftStartDistance_in;
		double rightStartDistance_in;
		bool startDistancesCalculated = false;

		Drive(Drivetrain *drivetrain, const double TOLERANCE_in);

	public:
		void Run() override;

		static void InitPID_SD();
		static void ControlPID_SD();

		virtual void PerformManeuver() = 0;
};