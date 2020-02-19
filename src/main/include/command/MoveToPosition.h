#pragma once

#include <vector>
#include <iostream>

#include "GlobalConstants.h"
#include "command/Command.h"
#include "command/MoveLength.h"
#include "command/RotateToAngle.h"
#include "CommandScheduler.h"

class MoveToPosition: public Command {
	private:
		CommandScheduler commandScheduler;

	public:
		MoveToPosition(
			frc::SpeedControllerGroup *leftDrive, 
			frc::SpeedControllerGroup *rightDrive, 
			const double X_in, 
			const double Z_in, 
			const double FINAL_ANGLE_rad, 
			const double LINEAR_TOLERANCE_in, 
			const double ANGULAR_TOLERANCE_in
		);

		void Run() override;
};