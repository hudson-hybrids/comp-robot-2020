#pragma once

#include <iostream>

#include "command/Drive.h"

class MoveLength: public Drive {
	private:
		const double LENGTH_in;

	public:
		MoveLength(frc::SpeedControllerGroup *leftDrive, frc::SpeedControllerGroup *rightDrive, const double LENGTH_in, const double TOLERANCE_in);

		void PerformManeuver() override;
};