#pragma once

#include <frc/controller/PIDController.h>
#include <frc/Encoder.h>
#include <frc/SpeedControllerGroup.h>

#include "command/Command.h"
#include "RobotMap.h"
#include "GlobalConstants.h"

class Drive: public Command {
	private:
		static const double P;
		static const double I;
		static const double D;

		void InitEncoders();

	protected:
		const double TOLERANCE_in;

		static frc2::PIDController pidController;

		static frc::Encoder leftDriveEncoder;
		static frc::Encoder rightDriveEncoder;
		static bool encodersInitialized;

		frc::SpeedControllerGroup *leftDrive;
		frc::SpeedControllerGroup *rightDrive;

		double leftStartDistance_in;
		double rightStartDistance_in;

		Drive(frc::SpeedControllerGroup *leftDrive, frc::SpeedControllerGroup *rightDrive, const double TOLERANCE_in);

	public:
		void Run() override;

		virtual void PerformManeuver() = 0;
};