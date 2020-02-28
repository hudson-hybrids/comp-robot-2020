#pragma once

#include "command/Command.h"
#include "command/MoveToPosition.h"
#include "NetworkTablesManager.h"
#include "VisionProcessingData.h"
#include "Drivetrain.h"

class AccurateAim: public Command {
	private:
		const double LINEAR_TOLERANCE_in;
		const double ANGULAR_TOLERANCE_in;

		NetworkTablesManager *networkTablesManager;
		Drivetrain *drivetrain;

		std::vector<VisionProcessingData> visionDataSet;

		bool isCollectingVisionData = false;
		MoveToPosition *moveToPosition = nullptr;

	public:
		AccurateAim(
			NetworkTablesManager *networkTablesManager,
			Drivetrain *drivetrain,  
			const double LINEAR_TOLERANCE_in, 
			const double ANGULAR_TOLERANCE_in
		);

		~AccurateAim();

		void Run() override;
};