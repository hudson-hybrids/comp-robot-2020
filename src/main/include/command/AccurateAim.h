#pragma once

#include <frc/SpeedControllerGroup.h>

#include "command/Command.h"
#include "command/MoveToPosition.h"
#include "NetworkTablesManager.h"
#include "VisionProcessingData.h"

class AccurateAim: public Command {
	private:
		MoveToPosition moveToPosition;

	public:
		AccurateAim(
			NetworkTablesManager *networkTablesManager,
			frc::SpeedControllerGroup *leftDrive, 
			frc::SpeedControllerGroup *rightDrive,  
			const double LINEAR_TOLERANCE_in, 
			const double ANGULAR_TOLERANCE_in
		);

		void Run() override;
};