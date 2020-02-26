#pragma once

#include "command/Command.h"
#include "command/MoveToPosition.h"
#include "NetworkTablesManager.h"
#include "VisionProcessingData.h"
#include "Drivetrain.h"

class QuickAim: public Command {
	private:
		RotateToAngle *rotateToAngle;

	public:
		QuickAim(
			NetworkTablesManager *networkTablesManager,
			Drivetrain *drivetrain,  
			const double ANGULAR_TOLERANCE_in
		);

		void Run() override;
};