#pragma once

#include <iostream>

#include <frc/smartdashboard/SmartDashboard.h>

#include "command/Drive.h"
#include "Drivetrain.h"

class RotateToAngle: public Drive {
	private:
		const double ANGLE_rad;

	public:
		RotateToAngle(Drivetrain *drivetrain, const double ANGLE_rad, const double TOLERANCE_in);

		void PerformManeuver() override;
};