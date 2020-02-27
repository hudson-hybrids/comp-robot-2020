#include "command/AccurateAim.h"

AccurateAim::AccurateAim(NetworkTablesManager *networkTablesManager, Drivetrain *drivetrain, const double LINEAR_TOLERANCE_in, const double ANGULAR_TOLERANCE_in) {
	const double VISION_DATA_TO_INCHES = 0;
	
	const double IDEAL_SHOOTING_X_TRANSLATION = 0;
	const double IDEAL_SHOOTING_Z_TRANSLATION = 0;

	const double IDEAL_SHOOTING_Y_ROTATION = 0;

	VisionProcessingData visionProcessingData = networkTablesManager->GetVisionProcessingData();

	const double X_DISPLACEMENT = VISION_DATA_TO_INCHES * (IDEAL_SHOOTING_X_TRANSLATION - visionProcessingData.ROBOT_X_TRANSLATION);
	const double Z_DISPLACEMENT = VISION_DATA_TO_INCHES * (IDEAL_SHOOTING_Z_TRANSLATION - visionProcessingData.ROBOT_Z_TRANSLATION);

	moveToPosition = new MoveToPosition(
		drivetrain, 
		X_DISPLACEMENT,
		Z_DISPLACEMENT,
		-visionProcessingData.ROBOT_Y_ROTATION,
		LINEAR_TOLERANCE_in,
		ANGULAR_TOLERANCE_in
	);
}

AccurateAim::~AccurateAim() {
	delete moveToPosition;
}

void AccurateAim::Run() {
	if (isFinished) {
		std::cout << "WARNING > CALL TO Run ON FINISHED AccurateAim" << std::endl;
	}
	else {
		moveToPosition->Run();

		if (moveToPosition->GetIsFinished()) {
			isFinished = true;
		}
	}
}