#pragma once

#include <frc/SpeedControllerGroup.h>

#include "command/Command.h"
#include "command/MoveToPosition.h"
#include "NetworkTablesManager.h"
#include "VisionProcessingData.h"
#include "Drivetrain.h"

class AccurateAim: public Command {
	private:
		MoveToPosition moveToPosition;

	public:
		AccurateAim(
			NetworkTablesManager *networkTablesManager,
			Drivetrain *drivetrain,  
			const double LINEAR_TOLERANCE_in, 
			const double ANGULAR_TOLERANCE_in
		);

		void Run() override;
};