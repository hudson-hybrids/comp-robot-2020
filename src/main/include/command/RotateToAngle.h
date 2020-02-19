#pragma once

#include <iostream>

#include "command/Drive.h"

class RotateToAngle: public Drive {
	private:
		const double ANGLE_rad;

	public:
		RotateToAngle(frc::SpeedControllerGroup *leftDrive, frc::SpeedControllerGroup *rightDrive, const double ANGLE_rad, const double TOLERANCE_in);

		void PerformManeuver() override;
};