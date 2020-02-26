#pragma once

#include <iostream>

#include <frc/smartdashboard/SmartDashboard.h>

#include "command/Drive.h"
#include "Drivetrain.h"

class MoveLength: public Drive {
	private:
		const double LENGTH_in;

		bool startDistanceFound = false;
		double leftStart = 0;
		double rightStart = 0;

	public:
		MoveLength(Drivetrain *drivetrain, const double LENGTH_in, const double TOLERANCE_in);

		void Run() override;
};